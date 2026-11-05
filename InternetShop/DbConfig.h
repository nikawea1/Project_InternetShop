//---------------------------------------------------------------------------
#ifndef DbConfigH
#define DbConfigH
//---------------------------------------------------------------------------
#include <vcl.h>

inline String GetDatabaseConnectionString()
{
	String exeDir = ExtractFilePath(Application->ExeName);
	String candidates[] = {
		exeDir + "BD_KURS.mdb",
		exeDir + "..\\..\\BD_KURS.mdb",
		exeDir + "..\\BD_KURS.mdb",
		exeDir + "Database\\BD_KURS.mdb",
		ExtractFilePath(ParamStr(0)) + "BD_KURS.mdb"
	};

	String dbPath = "";
	for (int i = 0; i < 5; ++i) {
		if (FileExists(candidates[i])) {
			dbPath = ExpandFileName(candidates[i]);
			break;
		}
	}

	if (dbPath.IsEmpty()) {
		dbPath = ExpandFileName(exeDir + "BD_KURS.mdb");
	}

	return "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + dbPath + ";Persist Security Info=False";
}

inline String GetImagePath(const String& fileName)
{
	if (fileName.IsEmpty()) return "";

	String cleanName = ExtractFileName(fileName);
	String exeDir = ExtractFilePath(Application->ExeName);

	String candidates[] = {
		exeDir + "Images\\" + cleanName,
		exeDir + "..\\..\\Images\\" + cleanName,
		exeDir + "..\\Images\\" + cleanName,
		exeDir + cleanName,
		cleanName
	};

	for (int i = 0; i < 5; ++i) {
		if (FileExists(candidates[i])) {
			return ExpandFileName(candidates[i]);
		}
	}

	return "";
}

//---------------------------------------------------------------------------
#endif
