#pragma once
#include "GameController.h"
#include "FormEnd.h"
#include <iostream>
namespace ZionEscape {
	using namespace std;
	using namespace System::Drawing;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormGame : public System::Windows::Forms::Form
	{
		Form^ formMenu;
		FormEnd^ formEnd;
		GameController^ game;
		Graphics^ g;
		BufferedGraphics^ bf;
		bool isResumed;

	private: System::Windows::Forms::Label^ rondaLbl;

	private: System::Windows::Forms::Timer^ animatorClock;
	public: //    void
		FormGame(Form^ form, bool resume): formMenu(form), isResumed(resume)
		{
			InitializeComponent();
			formEnd = gcnew FormEnd(formMenu);
			game = gcnew GameController(rondaLbl);
			g = this->CreateGraphics();
			bf = BufferedGraphicsManager::Current->Allocate(g, this->ClientRectangle);
		}

		void RestartGame() {
			game->SetDatosLevel(true);
			isResumed = false;
		}

	protected:
		~FormGame()
		{
			if (components)
			{
				delete components;
			}
			delete game; game = nullptr;
			delete formEnd; formEnd = nullptr;
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
			this->rondaLbl = (gcnew System::Windows::Forms::Label());
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
			// rondaLbl
			// 
			this->rondaLbl->AutoSize = true;
			this->rondaLbl->Location = System::Drawing::Point(433, 9);
			this->rondaLbl->Name = L"rondaLbl";
			this->rondaLbl->Size = System::Drawing::Size(51, 13);
			this->rondaLbl->TabIndex = 0;
			this->rondaLbl->Text = L"Ronda: 1";
			this->rondaLbl->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FormGame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(508, 448);
			this->Controls->Add(this->rondaLbl);
			this->MaximizeBox = false;
			this->Name = L"FormGame";
			this->Text = L"ZionEscape";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormGame::FormGame_FormClosed);
			this->Load += gcnew System::EventHandler(this, &FormGame::FormGame_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormGame::FormGame_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormGame::FormGame_KeyUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	Void clock_Tick(Object^ sender, EventArgs^ e) {
		//Clock para mostrar imagenes y movimientos
		if (!isResumed) { 
			game->NextLevel();
			game->ShowGame(bf->Graphics);
			game->MoveEntities(bf->Graphics);

			bf->Render(g);

			if (!game->isPlayerWithLife()) {
				this->Hide();
				formEnd->Show();
				formEnd->SetRondas(game->GetRondas());
				isResumed = true;
			}
		}
		
	}
	private: Void FormGame_KeyDown(Object^ sender, KeyEventArgs^ e) {
		game->KeyDown(e->KeyCode);
	}
	private: Void FormGame_KeyUp(Object^ sender, KeyEventArgs^ e) {
		game->KeyUp(e->KeyCode);
	}

	private: Void animatorClock_Tick(Object^ sender, System::EventArgs^ e) {
		//Este clock sirve para que las animaciones no vayan tan rapido
		game->AnimateEntities();
	}
	private: Void FormGame_Load(Object^ sender, EventArgs^ e) {
		if (isResumed == false) { game->Start(); }
		if (isResumed == true) { game->Resume(); isResumed = false; }
	}

	private: Void FormGame_FormClosed(Object^ sender, FormClosedEventArgs^ e) {
		formMenu->Close();
	}
};
}
