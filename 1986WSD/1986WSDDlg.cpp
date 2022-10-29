// 1986WSDDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "1986WSD.h"
#include "1986WSDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// диалоговое окно CMy1986WSDDlg




CMy1986WSDDlg::CMy1986WSDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1986WSDDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1986WSDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM, m_com);
	DDX_Control(pDX, IDC_FILE, m_file);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_ERASE, m_erase);
	DDX_Control(pDX, IDC_PROGRAM2, m_program);
	DDX_Control(pDX, IDC_VERIFY, m_verify);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDRUN, m_run);
}

BEGIN_MESSAGE_MAP(CMy1986WSDDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDBROWSE, &CMy1986WSDDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDSTART, &CMy1986WSDDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDRUN, &CMy1986WSDDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDSTART_RUN, &CMy1986WSDDlg::OnBnClickedSartRun)
END_MESSAGE_MAP()


// обработчики сообщений CMy1986WSDDlg

BOOL CMy1986WSDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Добавление пункта ''О программе...'' в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	if(!GetInitParam())
	{
		MessageBox("Ошибка открытия файла конфигурации","File Error",MB_OK|MB_ICONSTOP);
		CDialog::OnCancel();
		return 0;  
	}
	if(!GetBootCod())
	{
	    MessageBox("Ошибка открытия файла 1986_BOOT_UART.HEX","File Error",
			MB_OK|MB_ICONSTOP);
		CDialog::OnCancel();
		return 0;  
	}
	m_com.SetWindowTextA(InitParam.comname);
	m_file.SetWindowTextA(InitParam.filename);
	m_erase.SetCheck(BST_CHECKED);
	m_program.SetCheck(BST_CHECKED);
	m_verify.SetCheck(BST_CHECKED);
	str = "Подключите устройство к РС ";
	str += InitParam.comname;
	m_list.AddString(str);
	str = "Нажмите Start";
	InsertStrToList();
	

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMy1986WSDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей средой.

void CMy1986WSDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMy1986WSDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMy1986WSDDlg::GetInitParam(void)
{
CString strfn;
CFile file;
int i;

	i = GetModuleFileName(NULL,bufcurdir,512);
	if(i == 0)
		return 0;
	while(bufcurdir[i] !='\\')
		i--;
	bufcurdir[i] = 0;
	strfn = "\\1986WSD.cfg";
	strfn = bufcurdir + strfn;
	if(!file.Open(strfn,CFile::modeRead,NULL))
	{
		strcpy_s(InitParam.comname,"COM1");
		strcpy_s(InitParam.filename,"");
		if(!file.Open(strfn,CFile::modeCreate|CFile::modeWrite,NULL))
			return 0;
		file.Write(&InitParam,sizeof(InitParam));
		file.Close();
		return 1;
	}
	file.Read(&InitParam,sizeof(InitParam));
	file.Close();
	return 1;
}

void CMy1986WSDDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса
CString strfn;
CFile file;
	strfn = "\\1986WSD.cfg";
	strfn = bufcurdir + strfn;
	file.Open(strfn,CFile::modeCreate|CFile::modeWrite,NULL);
	file.Write(&InitParam,sizeof(InitParam));
	file.Close();
	CDialog::OnCancel();
}

void CMy1986WSDDlg::OnBnClickedBrowse()
{
	// TODO: добавьте свой код обработчика уведомлений
CFileDialog dlgFile(TRUE);
	dlgFile.GetOFN().lpstrFilter = "hex Files\0*.hex\0\0";
	dlgFile.DoModal();
	strcpy_s(InitParam.filename,dlgFile.GetPathName());
	m_file.SetWindowTextA(InitParam.filename);
}

DWORD WINAPI CMy1986WSDDlg::StartThreadFunction( LPVOID lpParam )
{
	((CMy1986WSDDlg*)lpParam)->Start();
	return 0;
}
void CMy1986WSDDlg::OnBnClickedStart()
{
	// TODO: добавьте свой код обработчика уведомлений
	fStartRun = FALSE;
	hthread = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            StartThreadFunction,       // thread function name
			this,			      // argument to thread function 
            0,                      // use default creation flags 
            &ThreadId);			   // returns the thread identifier
}
void CMy1986WSDDlg::Start(void)
{
int i,j;
BOOL f;
const char id_str[13]= "1986BOOTUART";

	if((m_program.GetCheck()==BST_CHECKED)||(m_verify.GetCheck()==BST_CHECKED))
	{
		if(!GetHexCod())
		{
			str = "Ошибка открытия HEX-файла!";
			InsertStrToList();			
			return;
		}
	}
	if(!com.Open(InitParam.comname))
	{
		str = "Ошибка открытия COM порта!";
		InsertStrToList();
		return;
	}
	
	str = "Синхронизация...";
	InsertStrToList();
	txdbuf[0] = 0x0;
	for(i=0;i<512;i++)
		com.WriteBlock(txdbuf,1);
	if	(!com.ReadBlock(rxdbuf,3))
	{
		for(i=0;i<512;i++)
			com.WriteBlock(txdbuf,1);		
		if	(!com.ReadBlock(rxdbuf,3))
		{
			str = "ошибка синхронизации!";
			InsertStrToList();		
			com.Close();
			return;
		}
	}

	m_list.DeleteString(m_list.GetCount()-1);
	str = "Синхронизация...ОК!";
	InsertStrToList();

	txdbuf[0] = 'B';
	txdbuf[1] = 0x0;
	txdbuf[2] = (char)0xc2;
	txdbuf[3] = 0x01;
	txdbuf[4] = 0x0;
	com.WriteBlock(txdbuf,5);
	while(com.ReadBlock(rxdbuf,1));

	com.dcb.BaudRate = CBR_115200;
	SetCommState(com.hCom, &com.dcb);
	txdbuf[0] = 0xd;
	com.WriteBlock(txdbuf,1);
	if	((!com.ReadBlock(rxdbuf,3))||(rxdbuf[0]!=0xd)||(rxdbuf[1]!=0xa)||(rxdbuf[2]!=0x3e))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return;
	}
	str = "baud rate 115200 OK!";
	InsertStrToList();
	str = "boot load...";
	InsertStrToList();
	txdbuf[0] = 'L';
	txdbuf[1] = dwadrboot & 0xff;
	txdbuf[2] = (dwadrboot>>8) & 0xff;
	txdbuf[3] = 0;
	txdbuf[4] = 0x20;
	txdbuf[5] = ilboot & 0xff;
	txdbuf[6] = (ilboot>>8) & 0xff;
	txdbuf[7] = 0;
	txdbuf[8] = 0;
	com.WriteBlock(txdbuf,9);
	if	((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!='L'))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return;
	}
	com.WriteBlock((LPSTR)(bufram+dwadrboot),ilboot);
	if	((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!='K'))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return;
	}
	for(i=0;i<(ilboot>>3);i++)
	{
		txdbuf[0] = 'Y';
		txdbuf[1] = (dwadrboot+8*i) & 0xff;
		txdbuf[2] = ((dwadrboot+8*i)>>8) & 0xff;
		txdbuf[3] = 0;
		txdbuf[4] = 0x20;
		txdbuf[5] = 8;
		txdbuf[6] = 0;
		txdbuf[7] = 0;
		txdbuf[8] = 0;
		com.WriteBlock(txdbuf,9);
		f = TRUE;
		if((com.ReadBlock(rxdbuf,10))&&(rxdbuf[0]=='Y')&&(rxdbuf[9]=='K'))
		{
			for(j=0;j<8;j++)
			{
				if(rxdbuf[j+1] != (char)bufram[dwadrboot+8*i+j])
					f= FALSE;
			}
		}
		else
			f= FALSE;
		if(!f)
		{
			str = "ошибка обмена";
			InsertStrToList();		
			com.Close();
			return;
		}
	}
	txdbuf[0] = 'R';
	txdbuf[1] = dwadrboot & 0xff;
	txdbuf[2] = (dwadrboot>>8) & 0xff;
	txdbuf[3] = 0;
	txdbuf[4] = 0x20;
	com.WriteBlock(txdbuf,5);
	if	((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!='R'))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return;
	}
	txdbuf[0] = 'I';
	com.WriteBlock(txdbuf,1);
	f = TRUE;
	if(com.ReadBlock(rxdbuf,12))
	{
		for(j=0;j<12;j++)
			{
				if(rxdbuf[j] != id_str[j])
					f= FALSE;
			}
	}
	else
		f = FALSE;
	if(!f)
	{
		str = "ошибка идентификации загрузчика!";
		InsertStrToList();		
		com.Close();
		return;
	}
	m_list.DeleteString(m_list.GetCount()-1);
	str = "boot load...ОК!";
	InsertStrToList();

	if(m_erase.GetCheck()==BST_CHECKED)
		if(!Erase())
			return;
	if(m_program.GetCheck()==BST_CHECKED)
		if(!Program())
			return;
	if(m_verify.GetCheck()==BST_CHECKED)
		if(!Verify())
			return;
	if(fStartRun)
	{
		str = "Run at 0x08000000...";
		InsertStrToList();
		txdbuf[0] = 'R';
		com.WriteBlock(txdbuf,1);
		if	((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!='R'))
		{
			str = "ошибка обмена";
			InsertStrToList();
		}
		else
		{
			m_list.DeleteString(m_list.GetCount()-1);
			str = "Run at 0x08000000 OK!";
			InsertStrToList();
		}	
	}
	com.Close();
}

void CMy1986WSDDlg::OnBnClickedRun()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_run.EnableWindow(0);
	if(!com.Open(InitParam.comname))
	{
		str = "Ошибка открытия COM порта!";
		InsertStrToList();
		return;
	}
	com.dcb.BaudRate = CBR_115200;
	SetCommState(com.hCom, &com.dcb);
	str = "Run at 0x08000000...";
	InsertStrToList();
	txdbuf[0] = 'R';
	com.WriteBlock(txdbuf,1);
	if	((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!='R'))
	{
		str = "ошибка обмена";
		InsertStrToList();
	}
	else
	{
		m_list.DeleteString(m_list.GetCount()-1);
		str = "Run at 0x08000000 OK!";
		InsertStrToList();
	}
	com.Close();
	return;
}

void CMy1986WSDDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_com.GetWindowTextA(InitParam.comname,6);
	str = "Подключите 1986ВЕ9x к РС ";
	str += InitParam.comname;
	InsertStrToList();
	str = "Нажмите Start";
	InsertStrToList();
//	CDialog::OnOK();
}

const char boot_hex_str[] = {
":020000042000DA\r\n"
":10780000907D002009780020054800474FF0006077\r\n"
":1078100004490860016881F3088840680047000057\r\n"
":107820000D7B002008ED00E000BF401C801E0028FA\r\n"
":10783000FBD1704700BFD7490988C1F34011002927\r\n"
":10784000F9D1D5490880704700BFD2480088C0F3FD\r\n"
":1078500000100028F9D1D1480088C0B2704710B597\r\n"
":10786000002300210BE0FFF7EFFF0246CC48007831\r\n"
":107870001044CB4C20701B0A12061344491C0429E7\r\n"
":10788000F1D3184610BD00B50246002304E0D0B283\r\n"
":10789000FFF7D0FF120A5B1C042BF8DB00BD00B51C\r\n"
":1078A000C048C14908610846006840F0010008600E\r\n"
":1078B0000846006820F4E0700860002220E0BB4821\r\n"
":1078C0000068B9494860B9480068001DB7490860B8\r\n"
":1078D000B548006840F4E070B34908600120FFF744\r\n"
":1078E000A3FFB148C068B24941F82200AE48006821\r\n"
":1078F00020F4E070AC4908600120FFF795FF521CAE\r\n"
":10790000402ADCDBA848006820F00100A649086096\r\n"
":1079100000BD10B5A74804680CB9FFF7C0FFA44923\r\n"
":1079200051F82400FFF7AFFF641CA14951F824006F\r\n"
":10793000FFF7A9FF641C04F03F009E49086010BDDA\r\n"
":1079400030B5002096490870002405E0FFF787FF56\r\n"
":10795000974941F82400641C402CF7D39148924980\r\n"
":1079600008610846006840F00100086008460068A9\r\n"
":1079700020F47750086000244BE08C4800682044D5\r\n"
":10798000894948600846006840F482500860062033\r\n"
":10799000FFF74AFF8448006840F4005082490860BD\r\n"
":1079A0000B20FFF741FF00251EE0804800682844B7\r\n"
":1079B00020447D494860601980087D4951F82000C5\r\n"
":1079C000794988600846006840F0800008603220ED\r\n"
":1079D000FFF72AFF7448006820F0800072490860B1\r\n"
":1079E0000120FFF721FF1035FF2DDED96E4800681A\r\n"
":1079F00020F480506C4908600620FFF715FF6A48A4\r\n"
":107A0000006820F40150684908600120FFF70CFF6E\r\n"
":107A1000241D102CB1D36448006820F00100624995\r\n"
":107A200008606248006800F58070604908605C4842\r\n"
":107A30000078FFF7FFFE30BD30B55A485A4908615B\r\n"
":107A40000846006840F00100086000242DE004F1C1\r\n"
":107A50000060554948600846006820F437500860C7\r\n"
":107A60000846006840F4446008600620FFF7DCFE2A\r\n"
":107A70004D48006840F400504B4908604CF25030CB\r\n"
":107A8000FFF7D2FE4848006820F48060464908604D\r\n"
":107A90006E20FFF7C9FE4448006820F42150424997\r\n"
":107AA00008600220FFF7C0FE241D102CCFD34FF03A\r\n"
":107AB000006417E03C484460006840F4E0703A49D4\r\n"
":107AC00008600120FFF7B0FE3748C568006820F461\r\n"
":107AD000E070354908600120FFF7A6FE681C00D061\r\n"
":107AE00003E0241D34488442E4D300BF2E480068DC\r\n"
":107AF00020F001002C4908604520FFF79BFE20463E\r\n"
":107B0000FFF7C1FE2846FFF7BEFE30BD10B50120CD\r\n"
":107B10002A49C8603DE0FFF797FE0446502C19D073\r\n"
":107B200006DC412C1CD0452C11D0492C30D104E06E\r\n"
":107B3000522C24D0562C2BD10FE0002404E02049F5\r\n"
":107B4000085DFFF777FE641C0C2CF8DB20E0FFF7E4\r\n"
":107B500073FF1DE0FFF7F4FE1AE0FFF7DAFE17E00F\r\n"
":107B600000200F490870FFF77AFE104908600020D6\r\n"
":107B7000104908600A480078FFF75CFE08E05220D0\r\n"
":107B8000FFF758FEC820FFF74FFEFFF73FFE00BF8C\r\n"
":107B900000BFC0E71880034000800340008003401E\r\n"
":107BA000087C00205155AA8A00800140007C0020FA\r\n"
":107BB0000C7C0020047C002000000208800340426E\r\n"
":107BC000C47B002031393836424F4F54554152540E\r\n"
":0C7BD000000000000000000000000000A9\r\n"
":0400000500000000F7\r\n"
":00000001FF\r\n"
};

BOOL CMy1986WSDDlg::GetBootCod(void)
{
int i,nb,j;
//CFile file;
CString strfn;
char chd;
DWORD	dwadr;
	dwadr_seg_hex = 0;
	dwadr_lineoffs_hex = 0;
	for(i=0;i<sizeof(bufram);i++)
	{
		bufram[i] = 0xff;
	}
	strfn = "\\1986_BOOT_UART.HEX";
	strfn = bufcurdir + strfn;
	//file.Open(strfn,CFile::modeRead,NULL);
	nb = 1;
	j = 0;
	while(j < ((sizeof(boot_hex_str) / sizeof(boot_hex_str[0])) - 1))
	{
		i = 0;
		do
		{
			//nb = file.Read(&chd,1);
			chd = boot_hex_str[j];
			j++;
			buf_hexstr[i] = chd;
			i++;			
		}
		while(chd!='\n');
		//if(nb != 1)
		//{
		//	//file.Close();
		//	for(i=0;i<sizeof(bufram);i++)
		//	{
		//		if(bufram[i] != 0xff)
		//			break;
		//	}
		//	dwadrboot = i;
		//	for(i=(sizeof(bufram)-1);i>=0;i--)
		//	{
		//		if(bufram[i] != 0xff)
		//			break;
		//	}
		//	ilboot = (i+16 - dwadrboot) & 0xfffffff7;;
		//	return 1;
		//}
		if(!GetDataHex())
		{
			//file.Close();
			return 0;
		}
		if(btype_hex == 0)
		{
			dwadr = dwadr_lineoffs_hex + dwadr_seg_hex + wadr_offs_hex;
			if((dwadr<0x20000000)||((dwadr+bl_hex)>0x20008000))
			{
				//file.Close();
				return 0;
			}
			dwadr -= 0x20000000;
			for(i=0;i<bl_hex;i++)
				bufram[dwadr+i] = buf_data_hex[i];
		}
	}

	for (i = 0; i < sizeof(bufram); i++)
	{
		if (bufram[i] != 0xff)
			break;
	}
	dwadrboot = i;
	for (i = (sizeof(bufram) - 1); i >= 0; i--)
	{
		if (bufram[i] != 0xff)
			break;
	}
	ilboot = (i + 16 - dwadrboot) & 0xfffffff7;;
	return 1;

	//return 0;
}

BOOL CMy1986WSDDlg::GetHexCod(void)
{
int i,nb;
CFile file;
CString strfn;
char chd;
DWORD	dwadr;
/*	
	for(i=0;i<sizeof(bufcod);i++)
	{
		bufcod[i] = i;
	}
	ilcod = 512*0x100;
	return 1;
*/
	dwadr_seg_hex = 0;
	dwadr_lineoffs_hex = 0;
	for(i=0;i<sizeof(bufcod);i++)
	{
		bufcod[i] = 0xff;
	}

	if(!file.Open(InitParam.filename,CFile::modeRead,NULL))
		return 0;
	nb = 1;
	while(nb == 1)
	{
		i = 0;
		do
		{
			nb = file.Read(&chd,1);
			buf_hexstr[i] = chd;
			i++;
		}
		while(chd!='\n');
		if(nb != 1)
		{
			file.Close();
			for(i=(sizeof(bufcod)-1);i>=0;i--)
			{
				if(bufcod[i] != 0xff)
					break;
			}
			if(i & 0xff)
				i = ((i + 0x100) & 0xffffff00);
			ilcod = i;
			return 1;
		}
		if(!GetDataHex())
		{
			file.Close();
			return 0;
		}
		if(btype_hex == 0)
		{
			dwadr = dwadr_lineoffs_hex + dwadr_seg_hex + wadr_offs_hex;
			if((dwadr<0x08000000)||((dwadr+bl_hex)>0x08020000))
			{
				file.Close();
				return 0;
			}
			dwadr -= 0x08000000;
			for(i=0;i<bl_hex;i++)
				bufcod[dwadr+i] = buf_data_hex[i];
		}
	}
	return 0;	
}

BYTE CMy1986WSDDlg::GetHexByte(int ibuf)
{
BYTE bh,bl;
	bh = buf_hexstr[ibuf] - 0x30;
	if (bh>9)
		bh -= 7;
	bh <<= 4;
	bl = buf_hexstr[ibuf+1] - 0x30;
	if (bl>9)
		bl -= 7;
	return bh+bl;
}

BOOL CMy1986WSDDlg::GetDataHex(void)
{
int i;
BYTE ks;
	if(buf_hexstr[0] != 0x3a)
		return	0;
	ks = 0;
	bl_hex = GetHexByte(1);
	wadr_offs_hex = ((WORD)GetHexByte(3)<<8)+GetHexByte(5);
	btype_hex = GetHexByte(7);
	ks = bl_hex + btype_hex + (wadr_offs_hex>>8) + wadr_offs_hex;
	for(i=0;i<bl_hex+1;i++)
	{
		buf_data_hex[i] = GetHexByte(2*i+9);
		ks += buf_data_hex[i];
	}
	if(ks!=0)
		return 0;
	if(btype_hex == 2)
		dwadr_seg_hex =	(((WORD)GetHexByte(9)<<8)+GetHexByte(11))<<4;
	if(btype_hex == 4)
		dwadr_lineoffs_hex = (((WORD)GetHexByte(9)<<8)+GetHexByte(11))<<16;
	return 1;
}

BOOL CMy1986WSDDlg::Erase(void)
{
DWORD	adr,data;	
	str = "Full chip erase...";
	InsertStrToList();
	txdbuf[0] = 'E';
	com.WriteBlock(txdbuf,1);
	Sleep(1000);
	if	((!com.ReadBlock(rxdbuf,9))||(rxdbuf[0]!='E'))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return 0;
	}
	adr = (BYTE)rxdbuf[1] + (((BYTE)rxdbuf[2])<<8) + (((BYTE)rxdbuf[3])<<16)
		+ (((BYTE)rxdbuf[4])<<24);
	data = (BYTE)rxdbuf[5] + (((BYTE)rxdbuf[6])<<8) + (((BYTE)rxdbuf[7])<<16)
		+ (((BYTE)rxdbuf[8])<<24);
	if((adr == 0x08020000)&&(data == 0xffffffff))
	{
		m_list.DeleteString(m_list.GetCount()-1);
		str = "Full chip erase done!";
		InsertStrToList();
		return 1;
	}
	m_list.DeleteString(m_list.GetCount()-1);
	str.Format("Full chip erase failed adr=0x%08x data=0x%08x",adr,data);
	InsertStrToList();
	com.Close();
	return 0;
}

BOOL CMy1986WSDDlg::Program(void)
{
int i,j;
BYTE ks;
	str.Format("Program %i byte...",ilcod);
	InsertStrToList();
	m_progress.SetRange(0,ilcod>>8);
	m_progress.SetPos(0);
	txdbuf[0] = 'A';
	txdbuf[1] = 0x00;
	txdbuf[2] = 0x00;
	txdbuf[3] = 0x00;
	txdbuf[4] = 0x08;
	com.WriteBlock(txdbuf,5);
	if((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!=0x08))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return 0;
	}
	txdbuf[0] = 'P';
	for(i=0;i<(ilcod>>8);i++)
	{
		com.WriteBlock(txdbuf,1);
		com.WriteBlock((LPSTR)(bufcod+(i<<8)),256);
		ks =0;
		for(j=0;j<256;j++)
			ks += bufcod[j+(i<<8)];
		if((!com.ReadBlock(rxdbuf,1))||((BYTE)rxdbuf[0]!=ks))
		{
			str = "ошибка обмена";
			InsertStrToList();		
			com.Close();
			return 0;
		}
		m_progress.SetPos(i+1);
	}
	m_list.DeleteString(m_list.GetCount()-1);
	str.Format("Program %i byte done!",ilcod);
	InsertStrToList();
	m_run.EnableWindow(1);
	return 1;
}

BOOL CMy1986WSDDlg::Verify(void)
{
int i,j,k;
	str = "Verify...";
	InsertStrToList();
	m_progress.SetRange(0,ilcod>>8);
	m_progress.SetPos(0);
	txdbuf[0] = 'A';
	txdbuf[1] = 0x00;
	txdbuf[2] = 0x00;
	txdbuf[3] = 0x00;
	txdbuf[4] = 0x08;
	com.WriteBlock(txdbuf,5);
	if((!com.ReadBlock(rxdbuf,1))||(rxdbuf[0]!=0x08))
	{
		str = "ошибка обмена";
		InsertStrToList();		
		com.Close();
		return 0;
	}
	txdbuf[0] = 'V';
	for(i=0;i<(ilcod>>8);i++)
	{
		for(j=0;j<32;j++)
		{
			com.WriteBlock(txdbuf,1);
			if(!com.ReadBlock(rxdbuf,8))
			{
				str = "ошибка обмена";
				InsertStrToList();		
				com.Close();
				return 0;
			}
			for(k=0;k<8;k++)
			{
				if((BYTE)rxdbuf[k] != bufcod[k+(j<<3)+(i<<8)])
				{
					
					m_list.DeleteString(m_list.GetCount()-1);
					str.Format("Verify failed adr=0x%08x dataw=0x%02x datar=0x%02x",
						0x08000000+k+(j<<3)+(i<<8),bufcod[k+(j<<3)+(i<<8)],(BYTE)rxdbuf[k]);
					InsertStrToList();
					com.Close();
					return 0;
				}
			}
		}
		m_progress.SetPos(i+1);
	}
	m_list.DeleteString(m_list.GetCount()-1);
	str.Format("Verify done!",ilcod);
	InsertStrToList();
	return 1;	
}

void CMy1986WSDDlg::InsertStrToList(void)
{
	int index;
	index = m_list.AddString(str);
	m_list.SetTopIndex(index);
}

void CMy1986WSDDlg::OnBnClickedSartRun()
{
	fStartRun = TRUE;
	hthread = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            StartThreadFunction,       // thread function name
			this,			      // argument to thread function 
            0,                      // use default creation flags 
            &ThreadId);			   // returns the thread identifier
}
