#include "Ball.h"
#include "template.h"
#include "Game.h"
#include "surface.h"
#include "Physics.h"
#include "GameObject.h"
#include <vector>


namespace Tmpl8
{
	Ball::Ball(float x, float y, Surface* sprite, vec2 v) : ballSprite(sprite, 1) {
		this->x = x;
		this->y = y;
		this->v = v;
		this->sprite = sprite;

		r = 15.0f;
		stop = false;

	}

	void Ball::Tick(float deltaTime, Surface* screen) {
		Move(deltaTime, screen);
		Draw(screen);
	}

	void Ball::Move(float deltaTime, Surface* screen) {
		bool noBounce = true;
		vec2 displacement = TotalDisplacement(x, y, 0.0001f, deltaTime);


		vec2 bounce = CalculateBounce(x, y, deltaTime, displacement);
		if (bounce != displacement + vec2(x, y) && bounce != vec2(NULL, NULL)) {
			//there has been a bounce
			x = bounce.x + x, y = bounce.y + y;
			noBounce = false;
		}

		vec2 nextPos = displacement + vec2(x, y);
		if (noBounce) {
			x = nextPos.x, y = nextPos.y;
		}
	}

	//void Ball::Move(float deltaTime, Surface* screen) {

	//    vec2 displacement = TotalDisplacement(x, y, 0.0001f, deltaTime);
	//    vec2 bounce = CalculateBounce(deltaTime, displacement);
	//    if (bounce != displacement) {
	//        //there has been a bounce
	//        x = bounce.x + x, y = bounce.y + y;

	//    }
	//    else {
	//        vec2 nextPos = displacement + vec2(x, y);
	//        x = nextPos.x, y = nextPos.y;
	//    }
	//}

	vec2 Ball::CalculateBounce(float xCircleCenter, float yCircleCenter, float totalDeltaTime, vec2 displacement) {
		std::vector<GameObject*> collidingBoundingBoxes = CheckBoundingBoxCollison();
		Impact impact;
		vec2 oldDisplacement;
		do {
			oldDisplacement = displacement;
			for (const auto& boundingBox : collidingBoundingBoxes)
			{
				do {
					impact = PointOfImpact(xCircleCenter, yCircleCenter, boundingBox, displacement);
					if (impact.pointOfImpact != vec2(NULL, NULL) && impact.elapsedDeltaTime != NULL) {
						displacement = Bounce(impact.pointOfImpact, impact.circleCenter, impact.elapsedDeltaTime, totalDeltaTime);
						totalDeltaTime = impact.elapsedDeltaTime;
						xCircleCenter = impact.circleCenter.x, yCircleCenter = impact.circleCenter.y;
					}
				} while (impact.pointOfImpact != vec2(NULL, NULL) && impact.elapsedDeltaTime != NULL);

			}
		  //check if another bounce should happen with the same or another object
		} while (displacement != oldDisplacement);
		
		return oldDisplacement;
	}

	/* bool Ball::OutOfBounds(vec2 position) {
		 return (position.x - r < 0 && position.y - r < 0 && position.x > ScreenWidth&& position.y > ScreenHeight);
	 }*/

	std::vector<GameObject*> Ball::CheckBoundingBoxCollison() {
		std::vector<GameObject*> collidingBoundingBoxes;

		for (const auto& obj : Game::myGameObjects)
		{
			BoundingBox myBoundingBox = GetBoundingBox();
			BoundingBox checkBoundingBox = obj->GetBoundingBox();
			//check if the checkBoundingBox isn't your own BoundingBox
			if (myBoundingBox.x1 != checkBoundingBox.x1 && myBoundingBox.y1 != checkBoundingBox.y1 && myBoundingBox.x2 != checkBoundingBox.x2 && myBoundingBox.y2 != checkBoundingBox.y2) {
				// do the BounidngBoxes collide?
				if (myBoundingBox.x1 <= checkBoundingBox.x2 && myBoundingBox.x2 >= checkBoundingBox.x1 && myBoundingBox.y1 <= checkBoundingBox.y2 && myBoundingBox.y2 >= checkBoundingBox.y1) {
					//yes there is a collision
					//return obj;
					collidingBoundingBoxes.push_back(obj);
				}
			}
		}
		return collidingBoundingBoxes;
	}

	BoundingBox Ball::GetBoundingBox() {
		return BoundingBox(x - r, y - r, x + r, y + r);
	}

	Ball::Impact Ball::PointOfImpact(float xCircleCenter, float yCircleCenter, GameObject* obstacle, vec2 displacement) {
		std::vector<vec2Equation> edgeVectors = obstacle->GetEdgeVectors();
		bool isCorner = false;
		float shortestDistance = NULL;
		vec2Equation closestEdgeVector;
		vec2 closestPoint;

		//select with which line of the object the ball has collided.
		for (const auto& edgeVector : edgeVectors) {
			vec2 p = vec2(xCircleCenter, yCircleCenter);
			vec2 a = edgeVector.position;
			vec2 b = edgeVector.direction + edgeVector.position;
			vec2 cp = ClosestPointOnSegment(p, a, b);

			float distance = (abs(sqrtf(powf(cp.x - p.x, 2) + powf(cp.y - p.y, 2))));

			if (shortestDistance == NULL || distance <= shortestDistance) {
				isCorner = (distance == shortestDistance);
				shortestDistance = distance;
				closestEdgeVector = edgeVector;
				closestPoint = cp;
			}
		}

		if (isCorner) {
			return CornerPointOfImpact(xCircleCenter, yCircleCenter, displacement, closestPoint);
		}
		else {
			return EdgePointOfImpact(xCircleCenter, yCircleCenter, displacement, closestEdgeVector);
		}
	}

	vec2 Ball::ClosestPointOnSegment(vec2 p, vec2 a, vec2 b) {
		//This function calculates the distance between a point and a line segment. I did not make this myself,
		// I got it from: https://www.youtube.com/watch?v=egmZJU-1zPU&ab_channel=Two-BitCoding
		vec2 ab = b - a;
		vec2 ap = p - a;
		vec2 cp;
		float proj = ap.dot(ab);
		float abLenSq = powf(ab.length(), 2);
		float d = proj / abLenSq;
		if (d <= 0) {
			cp = a;
		}
		else if (d >= 1) {
			cp = b;
		}
		else {
			cp = a + ab * d;
		}
		return cp;
	}

	Ball::Impact Ball::CornerPointOfImpact(float xCircleCenter, float yCircleCenter, vec2 displacement, vec2 corner) {
		// calculating the amount of deltatime elapsed until impact.
		// x(t) = x0 + fX * t
		// y(t) = y0 + fY * t
		// d(t) = sqrt((x(t) - x_c)^2 + (y(t) - y_c)^2)
		// d(t) = r
		// substitute x(t) and y(t) and solve for t
		// to solve this equation I used chatGPT4 to save time
		float a = powf(displacement.x, 2) + powf(displacement.y, 2);
		float b = 2 * (xCircleCenter * displacement.x - corner.x * displacement.x + yCircleCenter * displacement.y - corner.y * displacement.y);
		float c = powf(xCircleCenter, 2) - 2 * xCircleCenter * corner.x + powf(corner.x, 2) + powf(yCircleCenter, 2) - 2 * yCircleCenter * corner.y + powf(corner.y, 2) - powf(r, 2);
		float d = powf(b, 2) - 4 * a * c;
		if (d < 0) {
			return Impact(vec2(NULL, NULL), vec2(NULL, NULL), NULL);
		}
		float dT1 = (-b + sqrtf(d)) / (2 * a);
		float dT2 = (-b - sqrtf(d)) / (2 * a);
		float dT;

		//the smallest positive dT refers to the correct point of impact.
		if (dT1 <= dT2 && dT1 > 0) {
			dT = dT1;
		}
		else if (dT2 <= dT1 && dT1 > 0) {
			dT = dT2;
		}
		else {
			return Impact(vec2(NULL, NULL), vec2(NULL, NULL), NULL);
		}
		//impactCircleCenter + displacement.normalized() * r
		vec2 impactCircleCenter = vec2(xCircleCenter, yCircleCenter) + displacement * dT; //the position of the center of the circle at the time of impact.
		vec2 cornerPointOfImpact = corner - impactCircleCenter; //the position of the point of impact 
		vec2 circleCollisionPoint = vec2(xCircleCenter, yCircleCenter) + cornerPointOfImpact; //the position of the point of impact before the impact happened.

		//check if the collision point on the line is within reach of the totalVelocity of the ball.
		// sqrtf(powf(circleCollisionPoint.x - cornerPointOfImpact.x, 2) + powf(circleCollisionPoint.y - cornerPointOfImpact.y, 2))
		if (displacement.length() > (circleCollisionPoint - corner).length()) {
			return Impact(corner, impactCircleCenter, dT);
		}
		else {
			return Impact(vec2(NULL, NULL), vec2(NULL, NULL), NULL);
		}
	}

	Ball::Impact Ball::EdgePointOfImpact(float xCircleCenter, float yCircleCenter, vec2 displacement, vec2Equation closestEdgeVector) {
		float nLine, nDisplacement;
		float XLinePos = closestEdgeVector.position.x, YLinePos = closestEdgeVector.position.y;
		vec2 circleCollisionPoint; //the point of the circle that will hit the edge first.
		vec2 obstacleEdge = closestEdgeVector.direction;
		vec2 edgePointOfImpact; //the point the actual hit takes place.

		circleCollisionPoint = vec2(xCircleCenter, yCircleCenter) + obstacleEdge.clockwise().normalized() * r;

		//calculate the intersection between the line and the movement of the circleCollisionPoint.
		nLine = (circleCollisionPoint.y * displacement.x + XLinePos * displacement.y - circleCollisionPoint.x * displacement.y - YLinePos * displacement.x) / (obstacleEdge.y * displacement.x - obstacleEdge.x * displacement.y);
		nDisplacement = (YLinePos * obstacleEdge.x + circleCollisionPoint.x * obstacleEdge.y - XLinePos * obstacleEdge.y - circleCollisionPoint.y * obstacleEdge.x) / (displacement.y * obstacleEdge.x - displacement.x * obstacleEdge.y);
		edgePointOfImpact = circleCollisionPoint + displacement * nDisplacement;

		//check if this intersection is actually on the edge, and within reach of the velocity.
		if (nDisplacement <= 1 && nDisplacement >= 0 && nLine <= 1 && nLine >= 0) {
			vec2 impactCircleCenter = edgePointOfImpact + obstacleEdge.counterClockwise().normalized() * r;
			return Impact(edgePointOfImpact, impactCircleCenter, nDisplacement);
		}
		else {
			return Impact(vec2(NULL, NULL), vec2(NULL, NULL), NULL);
		}
	}



	void Ball::Draw(Surface* screen) {
		ballSprite.DrawScaled((int)(x - r), (int)(y - r), (int)(2 * r), (int)(2 * r), screen); //x-r,y-r : changes from ballCenter to top left corner.
	}


}