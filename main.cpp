#include <Novice.h>
#include <time.h>
#include<math.h>
#include<stdlib.h>

const char kWindowTitle[] = "LC1C";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 480, 736);

	struct Vector2 {
		float x;
		float y;
	};

	struct PLAYER {
		Vector2 pos;
		Vector2 velocity;
		Vector2 acceleration;
		int Alive;
	};

	float jumppower = 23;

	PLAYER Player = { {200,500},{0,0},{0,1.1},true };

	enum GameScene {
		TITLE,
		GAME,
		GAMEOVER,
		RESALT,
	};

	int gamescene = 1;

	float cloudposx=0;
	float cloudposy=350;
	float cloudspeed = 6;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		

		switch (gamescene) {
		case TITLE:

			

		break;

		case GAME:

			if (keys[DIK_SPACE]) {
				jumppower += 0.05;
			}

			if (jumppower > 32) {
				jumppower = 32;
			}

			if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] && Player.pos.y == 500) {
				Player.velocity.y = jumppower;
				jumppower = 23;
			}

			Player.velocity.x -= Player.acceleration.x;
			Player.velocity.y -= Player.acceleration.y;

			Player.pos.x -= Player.velocity.x;
			Player.pos.y -= Player.velocity.y;


			if (Player.pos.y > 500) {
				Player.pos.y = 500;
			}

			

			cloudposx += cloudspeed;

			if (cloudposx > 340) {
				cloudspeed *= -1;
			}

			if (cloudposx < 0) {
				cloudspeed *= -1;
			}

			Novice::DrawBox(Player.pos.x, Player.pos.y, 96, 128, 0.0f, WHITE, kFillModeSolid);

			Novice::DrawBox(cloudposx, cloudposy, 130, 40, 0.0f, WHITE, kFillModeSolid);

			break;

		case GAMEOVER:

			

			break;

		case RESALT:

			

			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::ScreenPrintf(0, 0, "%d",gamescene);

		Novice::ScreenPrintf(20, 0, "%f", jumppower);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
