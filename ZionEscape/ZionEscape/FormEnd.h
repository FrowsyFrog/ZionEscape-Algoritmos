#pragma once

namespace ZionEscape {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormEnd : public System::Windows::Forms::Form
	{
		Form^ formMenu;
		
	public:
		FormEnd(Form^ form): formMenu(form)
		{
			InitializeComponent();
		}

		void SetRondas(int value) {
			maxRoundLbl->Text = "MAX ROUND: " + value;
		}

	protected:
		~FormEnd()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ gameOverLbl;
	protected:

	private: System::Windows::Forms::Label^ maxRoundLbl;
	protected:

	private: System::Windows::Forms::Button^ btnExit;
	private: System::Windows::Forms::Button^ btnMenu;


	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->gameOverLbl = (gcnew System::Windows::Forms::Label());
			this->maxRoundLbl = (gcnew System::Windows::Forms::Label());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->btnMenu = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// gameOverLbl
			// 
			this->gameOverLbl->AutoSize = true;
			this->gameOverLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 49, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gameOverLbl->ForeColor = System::Drawing::Color::Silver;
			this->gameOverLbl->Location = System::Drawing::Point(33, 63);
			this->gameOverLbl->Name = L"gameOverLbl";
			this->gameOverLbl->Size = System::Drawing::Size(432, 88);
			this->gameOverLbl->TabIndex = 0;
			this->gameOverLbl->Text = L"GAME OVER";
			// 
			// maxRoundLbl
			// 
			this->maxRoundLbl->AutoSize = true;
			this->maxRoundLbl->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 19, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->maxRoundLbl->ForeColor = System::Drawing::Color::White;
			this->maxRoundLbl->Location = System::Drawing::Point(132, 218);
			this->maxRoundLbl->Name = L"maxRoundLbl";
			this->maxRoundLbl->Size = System::Drawing::Size(241, 31);
			this->maxRoundLbl->TabIndex = 1;
			this->maxRoundLbl->Text = L"MAX ROUND: 999";
			this->maxRoundLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnExit
			// 
			this->btnExit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Georgia", 13.97015F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnExit->ForeColor = System::Drawing::Color::Black;
			this->btnExit->Location = System::Drawing::Point(293, 339);
			this->btnExit->Margin = System::Windows::Forms::Padding(2);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(162, 41);
			this->btnExit->TabIndex = 6;
			this->btnExit->Text = L"Exit";
			this->btnExit->UseVisualStyleBackColor = false;
			this->btnExit->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormEnd::exitGame);
			// 
			// btnMenu
			// 
			this->btnMenu->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnMenu->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnMenu->Font = (gcnew System::Drawing::Font(L"Georgia", 13.97015F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMenu->ForeColor = System::Drawing::Color::Black;
			this->btnMenu->Location = System::Drawing::Point(48, 339);
			this->btnMenu->Margin = System::Windows::Forms::Padding(2);
			this->btnMenu->Name = L"btnMenu";
			this->btnMenu->Size = System::Drawing::Size(162, 41);
			this->btnMenu->TabIndex = 7;
			this->btnMenu->Text = L"Menu";
			this->btnMenu->UseVisualStyleBackColor = false;
			this->btnMenu->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormEnd::goMenu);
			// 
			// FormEnd
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(494, 413);
			this->Controls->Add(this->btnMenu);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->maxRoundLbl);
			this->Controls->Add(this->gameOverLbl);
			this->MaximizeBox = false;
			this->Name = L"FormEnd";
			this->Text = L"ZionEscape";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormEnd::FormGame_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void FormGame_FormClosed(Object^ sender, FormClosedEventArgs^ e) {
		formMenu->Close();
	}
	private: Void exitGame(Object^ sender, MouseEventArgs^ e) {
		formMenu->Close();
	}
	private: Void goMenu(Object^ sender, MouseEventArgs^ e) {
		formMenu->Show();
		this->Hide();
	}
};
}
