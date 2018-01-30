#ifndef CDAGSETNING
#define CDAGSETNING
#include "CStrengur.h"

class CDagsetning
{
public:
	CDagsetning(void);
	~CDagsetning(void);
	int		Paktar(unsigned int uiAr);
	int		Gyllitala(unsigned int uiAr);
	int		DagurPaskar(int iAr, int *iOutDagur);
	char *	NafnManadar(unsigned short usManudur=0);// skilar nafni m�na�ar
	char *	NafnVikudags(unsigned short usVikudagur, bool bLongName=true);//skilar nafni vikudags

protected:
		CStrengur m_cstr;// Kemur � sta� m_cTemp;
private:
	
	int m_iDagur;// Dagur dagsetningar
	int m_iManudur;// M�nu�ur dagsetningar
	int m_iAr;// �r dagsetningar
	//char *m_cTemp;// Temp breyta sem notu� er �egar fall �arf a� skyla streng.  Vara ver�ur vi� � l�singu fallsins a� innihaldi �essarar breytu ber a� afrita strax �v� �ll f�ll � klasanum sem skyla �urfi streng munu nota �essa breytu.
	// �etta fall skal bara kalla � �r constructor.  
	void initilize(void);
	unsigned int ArsManudurToDagar(int iAr, int iManudur);
	unsigned int ArsDagarToManudur(int iAr, unsigned int ArsManudarDagar);

public:
	// Athugar hvort vi�komandi dagsetning er h�t��ardagur.  Ef skilagildi er minna en 0 �� er vi�komandi dagur ekki h�t��ardagur ef skilagildi� er minna en 0 �� er vi�komandi dagur ekki h�t��ardagur en �a� er eitthva� s�rstakt vi� hann.  Nota m� skylagildi �essarar skipunar til �ess a� setja inn � falli� HatidIstreng
	virtual int erHatid(int iAr, int iManudur, int iDagur);
	// Falli� skilar nafni h�t��ar sem falli� erHatid fann. 
	virtual char * NafnHatidardags(int iHatidarIndex);
	unsigned short erJolasveinn(int iManudur, int iDagur);
	char * NafnJolasveins(unsigned short usJolasveinn);
	// Skilar nafni j�lasveins
	char * VisaJolasveins(unsigned short usJolasveinn);
	// Skilar v�su j�lasveins
	unsigned short vikudagur (int iAr, int iManudur, int iDagur);
	void DaysDelete(int *iAr, int *iManudur, int *iDagur, unsigned int uiRemove);
	void DaysAdd   (int *iAr, int *iManudur, int *iDagur, unsigned int uiAdd);
	bool erHlaupar(int iAr);
	bool erRimspillisar(int iAr);
	int	 FyrstiVikudagur(int iFinnaVikudag, int iAr, int iManudur, int iDagur=0);
	void DagurFostudagurinnLangi(int iAr, int *iManudur, int *iDagur);
	void DagurOskudagur(int iAr, int *iManudur, int *iDagur);
	void DagurHvitasunnudagur(int iAr, int *iManudur, int *iDagur);
	void DagurAnnar_i_Hvitasunnu(int iAr, int *iManudur, int *iDagur);
	void DagurUppstigningardagur(int iAr, int *iManudur, int *iDagur);
	void DagurFridagurVerslunarmanna(int iAr, int *iManudur, int *iDagur);
	void DagurSkirdagur(int iAr, int *iManudur, int *iDagur);
	void DagurAnnar_i_Paskum(int iAr, int *iManudur, int *iDagur);
	void DagurBolludagur(int iAr, int *iManudur, int *iDagur);
	void DagurSprengidagur(int iAr, int *iManudur, int *iDagur);
	void DagurPalmasunnudagur(int iAr, int *iManudur, int *iDagur);
	void DagurMaedradagur(int iAr, int *iManudur, int *iDagur);
	void DagurSjomannadagur(int iAr, int *iManudur, int *iDagur);
	void DagurAdventa(int iAr, int *iManudur, int *iDagur);
	void DagurSumardagurinnFyrsti(int iAr, int *iManudur, int *iDagur);
	void DagurVorjafndaegur(int iAr, int *iManudur, int *iDagur);
	void DagurHaustjafndaegur(int iAr, int *iManudur, int *iDagur);
	// Skilar dagafj�lda � m�nu�i
	int DagaFjoldi(int iAr, int iManudur);
	// Skilar fj�lda virkra daga fr� og me� dagsetningum tilteknum � f�ribreytum
	int FjoldiVirkraDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag);
	// Skilar fj�lda fr�daga daga fr� og me� dagsetningum tilteknum � f�ribreytum
	// Til fr�daga teljast helgidagar og h�t��ardagar
	int FjoldiFriDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag);
	bool erVirkurDagur(int iAr, int iManudur, int iDagur);
};

#endif //CDAGSETNING