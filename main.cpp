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
	public:
	float x = 100.f;
	float y = 100.f;
	float Height = 100.f;
	float Speed = 1;
	float CurrentAccelerate = 1;
	const int FallingAccelerate = 10;

	//getter
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
	//setter
	void SetX(int NewX) {
		this->x = NewX;
	}
	void SetY(int NewY) {
		this->y = NewY;
	}


	//Self Drawing?

};

class Player : public PhysicObject
{

public:
	/*
	Vector2 UpperLeft;
	Vector2 UpperRight;
	Vector2 LowerLeft;
	Vector2 LowerRight;
	*/
	void SetStart() {
		this->y = 100;
		this->x = 100;
		this->Height = 100;
	}
	int JumpForce = 60;
	Rectangle BodyCollider = { x,y,40,Height };
	void SetSpeed(int AmountToSet) {
		this->Speed = AmountToSet;
	}
	bool CheckGroundBelow(Rectangle Ground) {
		if (Ground.y < (this->y + this->Height) || (this->y + this->Height) > Ground.y+70) {
			this->CurrentAccelerate = 0;
			
			
			return 1;
		}
		else
		{
			
			//CurrentAccelerate = CurrentAccelerate + (FallingAccelerate);
			return 0;
		}
	}
	void move(Rectangle Ground) {
		y+=FallingAccelerate*GetFrameTime()*100;
		if (Ground.y < (this->y - this->Height)) {
			this->y -= this->y - Ground.y;
			std::cout << 3213819;
		}
	}

	void UpdateColliderState() {
		this->BodyCollider.x = x;
		this->BodyCollider.y = y;
		
	}

	Player(std::vector<Rectangle>GameColliderPtr = GameColliderPtr) {
		GameColliderPtr.push_back(this->BodyCollider);
	};
};

class Platform : public NonPhysicOblect
{
public:
	Rectangle Collider = { 0,700,1000,200 };
	void SetX() {
		this->x;
	}
	int GetY() {
		return this->y;
	}
};

template <typename T1>
void DrawArrays(std::vector<T1> Arr) {
	T1 CurrentItem = 0;

	Arr.size;
}



int main() {
	

	Player NewPlayer;
	Platform Ground;

	GameColliderPtr.push_back(NewPlayer.BodyCollider);
	GameColliderPtr.push_back(Ground.Collider);
	

	NewPlayer.SetStart();
	
	InitWindow(1920, 1080, "test");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({128,60,33,255});
		
		NewPlayer.UpdateColliderState();

		DrawRectangle(Ground.Collider.x, Ground.Collider.y, Ground.Collider.width, Ground.Collider.height, GREEN);
		
		DrawRectangle(NewPlayer.BodyCollider.x, NewPlayer.BodyCollider.y, NewPlayer.BodyCollider.width, NewPlayer.BodyCollider.height, RED);

		if (NewPlayer.CheckGroundBelow(Ground.Collider) == 0) {
			NewPlayer.move(Ground.Collider);
			
		}
		int f = GetKeyPressed();
		// a is 65
		//std::cout << f;
		
		if (IsKeyDown(262) == 1) {
			NewPlayer.SetX(NewPlayer.x + 10);
		}
		else
		{
			if (IsKeyDown(263) == 1) {
				NewPlayer.SetX(NewPlayer.x - 10);
			}
		}

		switch (f) {
		case 32:
			NewPlayer.SetY(NewPlayer.y - NewPlayer.JumpForce);
			break;
		}
		//NewPlayer.CheckGround(GameColliderPtr);
		
		EndDrawing();
	}

	return 0;
}