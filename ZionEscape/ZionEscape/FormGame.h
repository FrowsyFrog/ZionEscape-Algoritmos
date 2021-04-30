#pragma once
#include "GameController.h"

namespace ZionEscape {
	using namespace System::Drawing;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormGame : public System::Windows::Forms::Form
	{
		GameController^ game;

		Graphics^ g;
		BufferedGraphics^ bf;

	private: System::Windows::Forms::Timer^ animatorClock;
	public:
		FormGame(void)
		{
			InitializeComponent();
			game = gcnew GameController();

			g = this->CreateGraphics();
			bf = BufferedGraphicsManager::Current->Allocate(g, this->ClientRectangle);
		}

	protected:
		~FormGame()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ clock;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->animatorClock = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// clock
			// 
			this->clock->Enabled = true;
			this->clock->Interval = 33;
			this->clock->Tick += gcnew System::EventHandler(this, &FormGame::clock_Tick);
			// 
			// animatorClock
			// 
			this->animatorClock->Enabled = true;
			this->animatorClock->Interval = 160;
			this->animatorClock->Tick += gcnew System::EventHandler(this, &FormGame::animatorClock_Tick);
			// 
			// FormGame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(508, 448);
			this->Name = L"FormGame";
			this->Text = L"FormGame";
			this->Load += gcnew System::EventHandler(this, &FormGame::FormGame_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormGame::FormGame_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormGame::FormGame_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	Void clock_Tick(Object^ sender, EventArgs^ e) {
		//Clock para mostrar imagenes y movimientos
		game->ShowGame(bf->Graphics);
		game->MoveEntities(bf->Graphics);

		bf->Render(g);
	}
	private: Void FormGame_KeyDown(Object^ sender, KeyEventArgs^ e) {
		game->PlayerMovement(true, e->KeyCode);
	}

	private: Void FormGame_KeyUp(Object^ sender, KeyEventArgs^ e) {
		game->PlayerMovement(false, e->KeyCode);
	}

	private: Void animatorClock_Tick(Object^ sender, System::EventArgs^ e) {
		//Este clock sirve para que las animaciones no vayan tan rapido
		game->AnimateEntities();
	}
	private: Void FormGame_Load(Object^ sender, EventArgs^ e) {
		game->Generate();
	}

	};
}
