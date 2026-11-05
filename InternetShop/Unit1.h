//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TDataSource *DataSource1;
	TADOTable *ADOTable1;
	TTimer *Timer1;
	TADOQuery *ADOQuery1;
	TDBGrid *DBGrid1;
	TButton *Button1;
	TButton *Button2;
	TDBNavigator *DBNavigator1;
	TADOConnection *ADOConnection2;
	TDataSource *DataSource2;
	TADOTable *ADOTable2;
	TADOQuery *ADOQuery2;
	TDBGrid *DBGrid2;
	TAutoIncField *ADOQuery2id_;
	TWideStringField *ADOQuery2name_;
	TIntegerField *ADOQuery2cost_;
	TWideStringField *ADOQuery2category_;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TEdit *Edit1;
	TLabel *Label2;
	TButton *Button10;
	TButton *Button11;
	TLabeledEdit *LabeledEdit1;
	TLabeledEdit *LabeledEdit2;
	TLabeledEdit *LabeledEdit3;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TLabeledEdit *LabeledEdit4;
	TLabeledEdit *LabeledEdit5;
	TButton *Button15;
	TWideStringField *ADOQuery2foto_;
	TIntegerField *ADOQuery2kolvo_;
	TWideMemoField *ADOQuery2inf_;
	TButton *Button16;
	TADODataSet *ADODataSet1;
	TEdit *Edit2;
	TButton *Button17;
	TDBNavigator *DBNavigator2;
	TButton *Button18;
	TLabeledEdit *LabeledEdit6;
	TEdit *Edit3;
	TAutoIncField *ADOQuery1Код;
	TWideStringField *ADOQuery1user_;
	TWideStringField *ADOQuery1password_;
	TLabel *Label3;
	TButton *Button19;
	TButton *Button20;
	TButton *Button21;
	TLabeledEdit *LabeledEdit7;
	TButton *Button3;
	TToggleSwitch *ToggleSwitch1;
	TLabel *Label1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N3;
	TMenuItem *N2;
	TMenuItem *N4;
	TLabel *Label4;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid2CellClick(TColumn *Column);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall DBGrid2DblClick(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
	void __fastcall ToggleSwitch1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);

private:	// User declarations

	void ApplyTheme();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
