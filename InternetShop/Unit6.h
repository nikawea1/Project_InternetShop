//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TDateTimePicker *DateTimePicker1;
	TDBGrid *DBGrid1;
	TADOConnection *ADOConnection1;
	TDataSource *DataSource1;
	TADOQuery *ADOQuery1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TWideStringField *ADOQuery1user_;
	TIntegerField *ADOQuery1check_;
	TIntegerField *ADOQuery1id_;
	TWideStringField *ADOQuery1name_;
	TIntegerField *ADOQuery1cost_;
	TIntegerField *ADOQuery1kolvo_;
	TWideStringField *ADOQuery1adress_;
	TWideStringField *ADOQuery1pay_;
	TDateTimeField *ADOQuery1date_;
	TWideStringField *ADOQuery1time_;
	TButton *Button6;
	TLabel *Label1;
	void __fastcall DateTimePicker1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
