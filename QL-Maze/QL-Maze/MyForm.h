#pragma once

#include <iostream>
#include "Header.h"
#include <vector>

vector<vector<double>> init_mat(int size) {
	vector<vector<double>> lookup_table;
	for (int st = 0; st < size * size; st++) {
		vector<double> state;
		for (int at = 0; at < 4; at++) {
			state.push_back(0);
		}
		lookup_table.push_back(state);
	}
	return lookup_table;
}


vector<vector<double>> QTable;
bool found = false;

pair<int, int> coords;

namespace QLMaze {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			isTraining = false;
			InitializeComponent();
			timer1->Start();
			side = 20;
			size = pictureBox1->Size.Width / side;
			coords = { 2, size / 4 };
			init_state = (size * (size / 2)) + size / 2;
			state = init_state;
			epoch = 0;
			QTable = init_mat(size);
			LearningBox->Checked = true;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::CheckBox^ LearningBox;
	private: System::Windows::Forms::CheckBox^ OptimalBox;
	private: System::Windows::Forms::Button^ TrainBtn;

	private: System::ComponentModel::IContainer^ components;


	protected:

	private:
		bool isTraining;
		int state;
		int epoch;
	private: System::Windows::Forms::Timer^ timer2;
		   int size;
		int init_state;
		int side;
	private: System::Windows::Forms::Timer^ timer1;



		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->LearningBox = (gcnew System::Windows::Forms::CheckBox());
			this->OptimalBox = (gcnew System::Windows::Forms::CheckBox());
			this->TrainBtn = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->Location = System::Drawing::Point(75, 59);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(300, 300);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint_1);
			// 
			// LearningBox
			// 
			this->LearningBox->AutoSize = true;
			this->LearningBox->Location = System::Drawing::Point(118, 385);
			this->LearningBox->Name = L"LearningBox";
			this->LearningBox->Size = System::Drawing::Size(67, 16);
			this->LearningBox->TabIndex = 1;
			this->LearningBox->Text = L"Learning";
			this->LearningBox->UseVisualStyleBackColor = true;
			// 
			// OptimalBox
			// 
			this->OptimalBox->AutoSize = true;
			this->OptimalBox->Location = System::Drawing::Point(268, 385);
			this->OptimalBox->Name = L"OptimalBox";
			this->OptimalBox->Size = System::Drawing::Size(63, 16);
			this->OptimalBox->TabIndex = 2;
			this->OptimalBox->Text = L"Optimal";
			this->OptimalBox->UseVisualStyleBackColor = true;
			this->OptimalBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::OptimalBox_CheckedChanged);
			// 
			// TrainBtn
			// 
			this->TrainBtn->Location = System::Drawing::Point(183, 418);
			this->TrainBtn->Name = L"TrainBtn";
			this->TrainBtn->Size = System::Drawing::Size(75, 23);
			this->TrainBtn->TabIndex = 3;
			this->TrainBtn->Text = L"Train";
			this->TrainBtn->UseVisualStyleBackColor = true;
			this->TrainBtn->Click += gcnew System::EventHandler(this, &MyForm::TrainBtn_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Interval = 1;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(450, 467);
			this->Controls->Add(this->TrainBtn);
			this->Controls->Add(this->OptimalBox);
			this->Controls->Add(this->LearningBox);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyMaze";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// TODO
	// Create a Q Table of 0 for each state (1 case of mat = 5x5 pixel ?)
	// 4 Actions possibles (Left - Right - Up - Down) AND LATER add no move
	// Put reward somewhere in the grid (fix)
	// When on reward, value +100
	// Each move, value -1
	// Beginning :
	//		- Exploration (using Greedy policy)
	//		- Continue Until find reward (or a certain amount?)
	//		- Set random rate (r = 0.4 is good) to alternate between Exploration and Exploitation

	// Implementation Possible :
	//		- Grid
	//		- Using all the formula
	//		- Enum for actions


	private: System::Void TrainBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		isTraining = !isTraining;
	}


	private: System::Void pictureBox1_Paint_1(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		for (auto i = 0; i < size ; i++) {
			for (auto j = 0; j < size ; j++) {
				int action = max_element(QTable[i * size + j].begin(), QTable[i * size + j].end()) - QTable[i * size + j].begin();
				double val = QTable[i * size + j][action] + 50;
				if (QTable[i * size + j][action] > 0)
					val += ( ((double)QTable[i * size + j][action]) / 30) * 20;
				val /= 100;
				
				PointF p1, p2, p3;
				int r, g, b = 0;
				int margin = 5;
				switch (action)
				{
				case 0:
					//Yellow
					r = val * 255;
					g = val * 255;
					if (val > 0.8)
						b = 150 * val;
					p1 = PointF((j+1) * side - margin, i * side + margin);
					p2 = PointF(j * side + margin, i * side + side/2);
					p3 = PointF((j+1) * side - margin, (i+1) * side - margin);
					break;
				case 1:
					//Green
					g = val * 255;
					r = g / 2;
					if (val > 0.8) {
						b = 150 * val;
						r += (r / 2);
					}
					p1 = PointF(j * side + margin, (i+1) * side - margin);
					p2 = PointF(j * side + side / 2, i * side + margin);
					p3 = PointF((j+1) * side - margin, (i+1) * side - margin);
					break;
				case 2:
					//Magenta
					r = val * 255;
					b = val * 255;
					if (val > 0.8)
						g = 150 * val;
					p1 = PointF(j * side + margin, i * side + margin);
					p2 = PointF((j+1) * side - margin, i * side + side / 2);
					p3 = PointF(j * side + margin, (i+1) * side - margin);
					break;
				case 3:
					//Orange
					r = val * 255;
					g = r / 2;
					if (val > 0.8) {
						b = 150 * val;
						g += (g / 2);
					}
					p1 = PointF(j * side + margin, i * side + margin);
					p2 = PointF(j * side + side / 2, (i+1) * side - margin);
					p3 = PointF((j+1) * side - margin, i * side + margin);
				default:
					break;
				}
				System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(255, r, g, b));
				e->Graphics->FillRectangle(brush, Rectangle(j*side, i*side, side, side));
				Pen^ blackPen = gcnew Pen(Color::Black, 1.0f);
				e->Graphics->DrawLine(blackPen, p1,p2);
				e->Graphics->DrawLine(blackPen, p2, p3);
			}
		}
		System::Drawing::SolidBrush^ myBrush =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::Red);

		e->Graphics->FillEllipse(myBrush, Rectangle(coords.first * side, coords.second * side, side, side));

		System::Drawing::SolidBrush^ myBrush2 =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::Blue);

		e->Graphics->FillEllipse(myBrush2, Rectangle((state % size) * side, (state / size) * side, side, side));
		
		System::Drawing::SolidBrush^ myBrush3 =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
		e->Graphics->FillEllipse(myBrush3, Rectangle((size/3) * side, 0, side, (size/3 + size/2)*side));
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (isTraining && !OptimalBox->Checked)
		{
			int i = 0;
			while (i < 200) {
				state = train(state, size, QTable, found, OptimalBox->Checked, coords);
				if (found)
				{
					int i = (((float)rand() / (RAND_MAX + 1)) * size);
					int j = (((float)rand() / (RAND_MAX + 1)) * size);
					state = i * size + j;
					found = false;
				}
				i++;
			}
			pictureBox1->Refresh();
		}
	}

	private: System::Void OptimalBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		state = init_state;
		timer2->Interval = (OptimalBox->Checked) ? 120 : 1;
		if (OptimalBox->Checked)
			timer2->Start();
		else
			timer2->Stop();
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (isTraining) {
			state = train(state, size, QTable, found, OptimalBox->Checked, coords);
			if (found)
			{
				int i = (((float)rand() / (RAND_MAX + 1)) * size);
				int j = (((float)rand() / (RAND_MAX + 1)) * size);
				state = i * size + j;
				print_lookup_table(QTable, size);
				found = false;
			}
			pictureBox1->Refresh();
		}
	}
};
}
