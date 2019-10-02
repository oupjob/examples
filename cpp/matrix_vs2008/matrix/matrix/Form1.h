#pragma once

#include "data_structures.h"

namespace matrix {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//

			contact_list_ = new list;
			circuit_matrix_ = new matrix_2d;
			incidence_matrix_ = new matrix_2d;
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			if ( contact_list_ )
				delete contact_list_;
			if ( circuit_matrix_ )
				delete circuit_matrix_;
			if ( incidence_matrix_ )
				delete incidence_matrix_;

		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ListBox^  listBoxContacts;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;


	private: 
		list*		contact_list_;
		matrix_2d*	circuit_matrix_;
		matrix_2d*	incidence_matrix_;


	private: System::Windows::Forms::TextBox^  textBoxCircuitMat;
	private: System::Windows::Forms::TextBox^  textBoxIncidenceMat;


	protected: 

	private:
		/// <summary>
		/// ��������� ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ������������ ����� ��� ��������� ������������ - �� ���������
		/// ���������� ������� ������ ��� ������ ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBoxContacts = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->textBoxCircuitMat = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->textBoxIncidenceMat = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 451);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(143, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"������� ����...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// listBoxContacts
			// 
			this->listBoxContacts->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->listBoxContacts->FormattingEnabled = true;
			this->listBoxContacts->Location = System::Drawing::Point(12, 26);
			this->listBoxContacts->Name = L"listBoxContacts";
			this->listBoxContacts->Size = System::Drawing::Size(143, 420);
			this->listBoxContacts->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(143, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"������� ������ ���������";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(162, 9);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(623, 465);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->textBoxCircuitMat);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(615, 439);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"������� ������������� �����";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// textBoxCircuitMat
			// 
			this->textBoxCircuitMat->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->textBoxCircuitMat->Location = System::Drawing::Point(0, 0);
			this->textBoxCircuitMat->Multiline = true;
			this->textBoxCircuitMat->Name = L"textBoxCircuitMat";
			this->textBoxCircuitMat->Size = System::Drawing::Size(619, 443);
			this->textBoxCircuitMat->TabIndex = 1;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->textBoxIncidenceMat);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(615, 439);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"������� �������������";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// textBoxIncidenceMat
			// 
			this->textBoxIncidenceMat->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->textBoxIncidenceMat->Location = System::Drawing::Point(0, 0);
			this->textBoxIncidenceMat->Multiline = true;
			this->textBoxIncidenceMat->Name = L"textBoxIncidenceMat";
			this->textBoxIncidenceMat->Size = System::Drawing::Size(619, 439);
			this->textBoxIncidenceMat->TabIndex = 0;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(797, 486);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listBoxContacts);
			this->Controls->Add(this->button1);
			this->MaximumSize = System::Drawing::Size(805, 513);
			this->MinimumSize = System::Drawing::Size(805, 513);
			this->Name = L"Form1";
			this->Text = L"������� ������������ � �������������";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// ���������� ������� ������� �� ������ "������� ����"
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			// �������� ��� ����� �� �������
			OpenFileDialog^ file_dialog = gcnew OpenFileDialog; // ������ ������ �����
			int result = 1;
			if ( file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK ) {
				System::String^ file_name = file_dialog->FileName; // �������� ��� �����
				result = readContactList( file_name ); // �� ����������� ����� ������ ������� ������
			}
			if ( result != 0 ) { // � ������ ������ ������ ������
				System::Windows::Forms::MessageBox::Show(
					L"�� ������� ��������� ���� ������� ������"	
				);
				return;
			}

			showContactList(); // ���������� ������
			calculateMatrixes(); // ��������� �������
			// ������� �������:
			showMatrix( circuit_matrix_, textBoxCircuitMat );
			showMatrix( incidence_matrix_, textBoxIncidenceMat );
		}
	// ����� �������� ������
	private: void showContactList() { 
			this->listBoxContacts->Items->Clear(); // ������� ������ ������������ ������
			this->listBoxContacts->Items->Add( "[�������] [����] [�������]" ); // ��������� ���������
			for( 
				const list_node* ls_node = contact_list_->getHead(); // ����� ������ ������� ������
				ls_node != nullptr;	// ���� ��� �� ����� ��������� �� NULL (������ ���������) ...
				ls_node = ls_node->next_	// ... ����� ��������� �� ���� �������� ������
			) {
				// ������� �������� � listBox, �������� ���� ������ �� ������� 
				this->listBoxContacts->Items->Add( 
					System::String::Format( 
						"{0} {1} {2}",
						ls_node->element_number_,	// ����� ��������
						ls_node->circuit_number_,	// ����� ������������� ����
						ls_node->contact_number_	// ����� ��������
					)
				);
			}
		}
	// ������� ���������� ������ �� �����
	private: int readContactList( System::String^ path ) {
		contact_list_->clear();
		try {
			// ������ StreamReader^ reader ������������� ���������� ��� ������ �� �����
			System::IO::StreamReader^ reader = gcnew System::IO::StreamReader( path ); // ������ ������ �� �����
			try {
				System::String^ line; // ����������� ������
				array<String^>^ contact = gcnew array<String^>( 32 ); // ����������� ������ ����� ����������� 
				list_node* node; // ������� ������

				while( line = reader->ReadLine() ) { 
					contact = line->Split( ' ' ); // ��������� ������ �� ��������
					if ( contact->Length != 3 ) // ������ ���� ��� �����
						return 4;
					try {
						node = new list_node(); // ������� ������� � �������������� �� ����
						node->element_number_ = Int32::Parse( contact[ 0 ] );
						node->circuit_number_ = Int32::Parse( contact[ 1 ] );
						node->contact_number_ = Int32::Parse( contact[ 2 ] );

						contact_list_->pushBack( node );
					} catch (Exception^ e) { // � ������ ������ ������� ������� �� ���� � �������
						delete node;	// e - ���������� ��� �������� ����� �� ������
						return 4;
					}
				}
			} catch ( Exception^ e ) { // � ������, ���� ����� ������� ���������� ...
				return 2;	// ... ��� ������ �������� reader ����� �����
			}
		} catch ( Exception^ e ) {
			return 1;	// ��������� ���������� ������ �������� �����
		}
		return 0;	// �������� ��������� ���������� �������
	}
	// ������ ������� ������
	private: void calculateMatrixes() {
		circuit_matrix_->buildCircuitMatFromContactList( contact_list_ );
		incidence_matrix_->buildiIncidenceMatFromContactList( contact_list_ );
	}
	// ����� ������� *matrix � text_box, ��. ����� �������
	private: void showMatrix( matrix_2d* matrix, System::Windows::Forms::TextBox^ text_box ) {
		int i, j, m, n; // ������� ������ � �������, ���������� ����� � ��������.
		
		m = matrix->getRowCount() + 1;	// �������� ����������� �������
		n = matrix->getColumnCount();	// 
		System::String^ row = "";	// ������ ��������� ��������������� ������ � ��������� ���
		
		// ����� ����������� �������
		text_box->Text += String::Format( "����������� �������: {0} x {1}", m - 1, n );
		text_box->Text += Environment::NewLine;
		text_box->Text += Environment::NewLine;

		// ����� ������� ������ � �������� ����� � ��������
		// �� ���� �������...
		for( i = 0; i <= m; i++ ) {
			row = "";	// ������ ��������� ������ � ������ �������� ����� ���������
			
			// �� ���� ��������
			for( j = 0; j <= n; j++ ) {
				if ( i == 0 && j < n ) { // ����� ������� ��������
					if ( j == 0 ) // ���� �� ��������� � ������ (0,0) -- ������� ������� � �����������
						row = "     | ";
					// ��� ������� �������� ����������� 4 �������
					// ��� ������� ����� ��������� �����������
					row = row + String::Format( "{0,4}", j + 1 ); 
				} else if ( i == 1 ) { // ����� ��������������� �����������
					row = row + "-----";
				} else if ( i > 1 && j == 0 ) { // ����� ������� �����
					row += String::Format( "{0,4} | ", i - 1 ); 
				} else if ( i > 1 ) { // ����� �������� �������
					row += String::Format( "{0,4}", matrix->getElement( i - 2, j - 1 ) );
				}
			}
			text_box->Text += row + Environment::NewLine;
		}
	}
	};
}

