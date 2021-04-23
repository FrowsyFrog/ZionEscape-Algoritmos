#pragma once
#include "GameController.h"

namespace ZionEscape {

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
	private: System::Windows::Forms::Timer^ animatorClock;
		   BufferedGraphics^ bf;

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
			this->ClientSize = System::Drawing::Size(754, 529);
			this->Name = L"FormGame";
			this->Text = L"FormGame";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormGame::FormGame_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormGame::FormGame_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	Void clock_Tick(Object^ sender, EventArgs^ e) {
		//Clock para mostrar imagenes y movimientos
		Graphics^ g = this->CreateGraphics();
		bf->Graphics->Clear(Color::White);
		game->ShowGame(bf->Graphics);
		game->MoveEntities(bf->Graphics);

		bf->Render(g);
	}
	private: System::Void FormGame_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		game->PlayerMovement(true, e->KeyCode);
	}

	private: System::Void FormGame_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		game->PlayerMovement(false, e->KeyCode);
	}

	private: System::Void animatorClock_Tick(System::Object^ sender, System::EventArgs^ e) {
		//Este clock sirve para que las animaciones no vayan tan rapido
		game->AnimateEntities();
	}
	};
}
