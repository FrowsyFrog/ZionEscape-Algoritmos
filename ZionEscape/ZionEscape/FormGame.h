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
	private: System::Windows::Forms::Timer^ animatorClock;

	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
		   BufferedGraphics^ bf;

	public:
		FormGame(void)
		{
			InitializeComponent();
			game = gcnew GameController();
			Bitmap^ bmpSolid = gcnew Bitmap("Sprites\\MapBlocks\\bmpSuelo.png");
			Bitmap^ bmpBase = gcnew Bitmap("Sprites\\MapBlocks\\bmpSolido.png");

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
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
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
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(271, 275);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(200, 22);
			this->dateTimePicker1->TabIndex = 0;
			// 
			// FormGame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1005, 651);
			this->Controls->Add(this->dateTimePicker1);
			this->Margin = System::Windows::Forms::Padding(4);
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
		Graphics^ g = this->CreateGraphics();
		bf->Graphics->Clear(Color::White);
		game->ShowGame(bf->Graphics);
		game->MoveEntities(bf->Graphics);
		game->Draw(bf->Graphics, bmpBase, bmpSolid); //ARREGLAR ESTO Y AVISAR LOS CAMBIOS QUE HIZO PLS
		//(tengo que cambiar unas cositas mas porque creo que no se esta generando un caminito de salida)
		bf->Render(g);
		delete bf, g;
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
	private: System::Void FormGame_Load(System::Object^ sender, System::EventArgs^ e) {
		game->Generate();
	}
};
}
