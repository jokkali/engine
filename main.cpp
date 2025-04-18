#include <iostream>
#include <vector>
#include "raylib.h"

std::vector<Rectangle> GameColliderPtr;

class NonPhysicOblect {
protected:
	int x;
	int y;
	bool isStatic;
public:
	int GetX() {
		return this->x;
	}
};

class PhysicObject {
protected:
	int x;
	int y;
	uint8_t Speed;
	uint8_t CurrentAccelerate;
	const float FallingAccelerate = 9.8;
public:
	int GetX() {
		return this->x;
	}
	int GetY() {
		return this->y;
	}
	uint8_t GetSpeed() {
		return this->Speed;
	}
	uint8_t GetCurrentAccelerate() {
		return this->CurrentAccelerate;
	}
};

class Player : public PhysicObject
{

public:
	Rectangle BodyCollider = { 100,100,10,10};
	void SetStart() {
		this->y = 100;
		this->x = 100;
	}
	void SetSpeed(int AmountToSet) {
		this->Speed = AmountToSet;
	}
	bool CheckGroundBelow(std::vector<Rectangle> Platforms) {
		if (Platforms[1].y > this->y - this->CurrentAccelerate || Platforms[1].y-Platforms[1].width < this->y - this->CurrentAccelerate) {
			this->CurrentAccelerate = 0;	
			return 1;
		}
		else
		{
			CurrentAccelerate = CurrentAccelerate + (FallingAccelerate);
			return 0;
		}
	}
	void Accelerate() {
		if (this->CheckGroundBelow(GameColliderPtr) == 1) {
			this->CurrentAccelerate = 0;
		}
		else
		{
			this->y = y - CurrentAccelerate;
			this->CurrentAccelerate += FallingAccelerate;
			
		}
	}
};

class Platform : public NonPhysicOblect
{
public:
	Rectangle Collider = { 100,1000,800,70 };
	void SetX() {
		this->x;
	}
	int GetY() {
		return this->y;
	}
};

int main() {
	

	Player NewPlayer;
	Platform Ground;

	GameColliderPtr.push_back(NewPlayer.BodyCollider);
	GameColliderPtr.push_back(Ground.Collider);
	//std::cout<< (int)NewPlayer.GetSpeed();

	NewPlayer.SetStart();

	InitWindow(1920, 1080, "test");

	SetTargetFPS(60);
	bool reg = 0;
	bool glob = 0;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({128,60,33,255});
		
		DrawRectangle(NewPlayer.BodyCollider.x, NewPlayer.BodyCollider.y, NewPlayer.BodyCollider.width, NewPlayer.BodyCollider.height, RED);
		DrawRectangle(Ground.Collider.x, Ground.Collider.y, Ground.Collider.width, Ground.Collider.height, GREEN);
		
		NewPlayer.Accelerate();
		//NewPlayer.CheckGround(GameColliderPtr);

		EndDrawing();
	}

	return 0;
}