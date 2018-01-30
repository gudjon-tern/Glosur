#include "DagsFile.h"

CDagsFile::CDagsFile(void)
{
	reset();
}
void CDagsFile::reset(void)
{
	m_iYear=0;
	m_iMonth=0;
	m_iDay=0;
	m_cstrType="";
	m_cstrName="";
	m_cstrComment="";
}

CDagsFile::~CDagsFile(void)
{
}

// er h�t��
int CDagsFile::erHatid(int iAr, int iManudur, int iDagur)
{	
	//H�t��adagar Posit�f skilagildi
	if ( 8==iManudur && 11==iDagur )
		return 100; //H�t��ardagur H�fundur (Gu�j�n H�lm) � afm�li.

  //A�rir dagar negat�f skilagildi
	if ( 12==iManudur && 28==iDagur )
		return -100; //barnadagur (28. desember), minningardagur um b�rnin � Betlehem, sem Her�des konungur mikli l�t taka af l�fi samkv�mt fr�s�gn Matteusargu�spjalls.

	//Skilum bara e�lilegum h�t��um.
	return CDagsetning::erHatid(iAr,iManudur,iDagur);
}

// Skilar nafni H�t��ardags
char * CDagsFile::NafnHatidardags(int iHatidarIndex)
{	if (iHatidarIndex > -100 && iHatidarIndex < 100)
		return CDagsetning::NafnHatidardags(iHatidarIndex);
	unsigned short us;
	if (iHatidarIndex<0)//Ekki h�t��ardagur en til er textastrengur fyrir vi�komandi dagsetningu
	{
		us=iHatidarIndex*-1;
		switch(us)
		{
			case 100	: m_cstr="barnadagur";		break;
			default		: return 0;
		}//switch(us)
		return m_cstr.getString();
	}//if (iHatidarIndex<0)
	us=iHatidarIndex;

	switch(us)//H�t��ardagur
	{
		case 100	: m_cstr="Afm�lisdagur Gu�j�ns";				break;
		default		: return 0;
	}
	
	return m_cstr.getString();
}
/*	If an instance of the doc parameter does not exist the function creates an instance 
	of it with the gcnew and initilized the CDagsFile to work vi� that document.

	If the file CDAGSFILE_FILENAME does exists    the function Loads the file.
	If the file CDAGSFILE_FILENAME does NOT exist the function Creates the file. (Not Implemted yet)
		
	Returns false if the XmlDocument could not be initilized
		
	Example on usage:
		CDagsFile dFile;
		XmlDocument ^doc;
		if (!dFile.InitFile(&doc))
			System::Windows::Forms::MessageBox::Show("Unable to initialize \n\nThat's to bad.");
*/
bool CDagsFile::InitFile( System::Xml::XmlDocument ^* doc)
{

	try
	{	if(!(*doc))
			(*doc)= gcnew XmlDocument();
		(*doc)->Load(CDAGSFILE_FILENAME);
	}//try
	catch (System::IO::FileNotFoundException ^err)
	{	
		(*doc)->LoadXml( "<g�gn></g�gn>" );
		XmlElement^ root =(*doc)->DocumentElement;
		try
			{
				(*doc)->Save( CDAGSFILE_FILENAME );
			}
	   catch(System::UnauthorizedAccessException ^err)
			{//skr�in er read only e�a hef ekki leifi af einhverjum �st��um
				return false;
			}

	}//catch
	
	return true;

}//bool CDagsFile::InitFile( System::Xml::XmlDocument ^* doc)



CStrengur CDagsFile::strToCstr(System::String ^str)
{
	CStrengur cstr="";// //how to convert from String ^ to CStrengur (wchar problem)
	for(int i=0;i<str->Length;i++) 
		cstr.cat((char)(wchar_t)str[i]);
	return cstr;
}

// S�kir fyrsta element � skr�nni. 
// ��ur: �arf a� vera b�i� a� kalla � falli� InitFile
System::Xml::XmlNode ^ CDagsFile::lesaFremst( System::Xml::XmlDocument ^ doc)
{	XmlNode ^parentNode;
	if(!doc)	return parentNode;//falli� InitFile ekki ekki b�i� a� Initilize
	//    "/g�gn/DateItem"
	parentNode=doc->SelectSingleNode(CDAGSFILE_ITEMPATH);
	if(!parentNode)	return parentNode;//shit, houston we have a-a problem
	
	lesa(parentNode);
	
	return parentNode;
}
System::Xml::XmlNode ^ CDagsFile::lesaNaest(System::Xml::XmlNode ^inNode)
{	XmlNode ^parentNode;
	if(!inNode)	return inNode;//shit, houston we have a-a problem
	parentNode=inNode->NextSibling;
	if(!parentNode)	return parentNode;//shit, houston we have a-a problem
	lesa(parentNode);
	
	return parentNode;
}
void CDagsFile::lesa(System::Xml::XmlNode ^inNode)
{	XmlNode ^childNode;
	reset();
	if(!inNode)	return;
	childNode=inNode->SelectSingleNode(CDAGSFILE_TYPE);   if(childNode) m_cstrType   =strToCstr(childNode->InnerText);
	childNode=inNode->SelectSingleNode(CDAGSFILE_NAME);   if(childNode) m_cstrName   =strToCstr(childNode->InnerText);
	childNode=inNode->SelectSingleNode(CDAGSFILE_COMMENT);if(childNode) m_cstrComment=strToCstr(childNode->InnerText);
	childNode=inNode->SelectSingleNode(CDAGSFILE_YEAR);   if(childNode) m_iYear = (strToCstr(childNode->InnerText).toLong());
	childNode=inNode->SelectSingleNode(CDAGSFILE_MONTH);  if(childNode) m_iMonth = (strToCstr(childNode->InnerText).toLong());
	childNode=inNode->SelectSingleNode(CDAGSFILE_DAY);    if(childNode) m_iDay = (strToCstr(childNode->InnerText).toLong());
}
System::Xml::XmlNode ^ CDagsFile::finnaFremst(System::String ^strVariable,System::String ^strFindMe, System::Xml::XmlDocument ^ doc)
{	/*	TODO: finnaFremst Sko�a�u  �etta til a� nota SelectSingleNode (mun betra held �g)
		http://msdn.microsoft.com/en-us/library/system.xml.xmlnode.selectsinglenode.aspx
	*/
	XmlNode ^parentNode, ^childNode;
	if(!doc)	return parentNode;//falli� InitFile ekki ekki b�i� a� Initilize
	//    "/g�gn/DateItem"
	System::String ^str=CDAGSFILE_ITEMPATH;
	str+=strVariable;
	parentNode=doc->SelectSingleNode(CDAGSFILE_ITEMPATH);
	if(!parentNode)	return parentNode;//shit, houston we have a-a problem
	
	childNode=parentNode->SelectSingleNode(strVariable);
	if(strFindMe==childNode->InnerText) 
		return parentNode;//found
	return finnaNaest(strVariable, strFindMe, parentNode);
}

System::Xml::XmlNode ^ CDagsFile::finnaNaest (System::String ^strVariable, System::String ^strFindMe, System::Xml::XmlNode     ^inNode)
{	XmlNode ^parentNode, ^childNode;
	if(!inNode)	return inNode;//shit, houston we have a-a problem
	parentNode=inNode->NextSibling;

	while(parentNode)
	{
		childNode=parentNode->SelectSingleNode(strVariable);
		if(strFindMe==childNode->InnerText) 
			return parentNode;//found
		
		parentNode=parentNode->NextSibling;	
	}
		return parentNode; //not found
}
// B�tir vi� n�rri f�rslu aftast � skr�nna
bool CDagsFile::skrifaAftast(char * strType, char * strName, char * strComment, int iYear, int iMonth, int iDay, System::Xml::XmlDocument ^ doc)
{
	//TODO: Athuga � hva�a formati �arf a� geyma Dagsetningingu og t�ma.
	/*	�g held a� sni�ugast s� a� dags. og t�ma � strengjabreitu : dd.mm.yyyy kk:mm
		Geyma �arf hven�r dateItem byrjar og hven�r �a� endar.
		d�mi um g�gn � skr�nni.
		<start>07.10.2008 05:22</start>
		<end>07.10.2008 05:30</end>
		Ef �a� er veri� a� skr� �kve�na dagsetningu �� mundi �a� skr�st svona
		<start>07.10.2008 00:00</start>
		<end>07.10.2008 00:00</end>

		Huglei�ing: hvernig � a� skr� eitthva� sem � alltaf a� gerast � vikud�gunum:
		laugard�gum og sunnud�gum?  � a� skr� �a� � 2mur f�rslum e�a � a� �tb�a format
		til a� �a� s� haldi� utanum lau. og sun. � sama DateItem.
		Ef svo er �arf a� b�a til breytu sem getur veri� breytileg eins og t.d.
		<type>weekly</type>
		<start>07.10.2008 10:00</start>
		<end>28.10.2008 00:00</end>
		<specialdata>0 6</specialdata>
		�etta mun hafa itemi� virkt 3 vikur (21 dag (ekki me� tali� 28.))
		�etta er ekki n�g, ef �g vil tiltaka t�mann fr� 8:00 til 8:20  hvar yr�i �a� sett
		yr�i t�minn � start og end nota�ur.  En s� t�mi � � �essu tilviki a� ver fyrir hven�r
		�essi series er �trunnin.
		�arf kanski a� b�a til series items, og vista �au vi� hli� occurrence � sta� dateitem.
		<g�gn>
			<occurrence>
			</occurrence>
			<series>
			</series>
		</g�gn>
	*/
	   XmlElement ^ root;
	   XmlNode ^childNode, ^parentNode;
	   root = doc->DocumentElement;
	   CStrengur cstrYear, cstrMonth, cstrDay;
				cstrYear=iYear;
				cstrMonth=iMonth;
				cstrDay=iDay;
	   if(!root) return false;
       parentNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_ITEM,	"");
	   if(!parentNode) return false;
	   
	   childNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_TYPE,	""); childNode->InnerText = gcnew System::String(strType);				parentNode->AppendChild(childNode);
	   if(!childNode) return false;

	   childNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_NAME,	""); childNode->InnerText = gcnew System::String(strName);				parentNode->AppendChild(childNode);
	   childNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_COMMENT,	""); childNode->InnerText = gcnew System::String(strComment);			parentNode->AppendChild(childNode);
	   childNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_YEAR,	""); childNode->InnerText = gcnew System::String(cstrYear.getString());	parentNode->AppendChild(childNode);
	   childNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_MONTH,	""); childNode->InnerText = gcnew System::String(cstrMonth.getString());parentNode->AppendChild(childNode);
	   childNode = doc->CreateNode(XmlNodeType::Element, CDAGSFILE_DAY,		""); childNode->InnerText = gcnew System::String(cstrDay.getString());	parentNode->AppendChild(childNode);
       root->AppendChild(parentNode);

	   try
	   {
			doc->Save( CDAGSFILE_FILENAME );
	   }
	   catch(System::UnauthorizedAccessException ^err)
	   {//skr�in er read only
		   
		   return false;
	   }
//An unhandled exception of type 'System.UnauthorizedAccessException' occurred in mscorlib.dll
//Additional information: Access to the path 'c:\Documents and Settings\Gudjon\My Documents\Visual Studio 2008\Projects\WinFormApp\WinFormApp\data.xml' is denied.

	return true;
}
