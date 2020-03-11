#include "dialogHelp.h"
#include "ui_dialogHelp.h"
#include <QDate>
#include <QTime>
#include <QUrl>
#include <windows.h>

DialogHelp::DialogHelp(bool bAbout, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    //��ֹ����
    this->setFixedSize(this->width(),this->height());
    //����ˮƽ���������ɼ�
    this->ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //���ɱ༭
    this->ui->textBrowser->setReadOnly(true);
    //ʹ��ϵͳĬ���������
    this->ui->textBrowser->setOpenLinks(false);

    QObject::connect(this->ui->textBrowser, &QTextBrowser::anchorClicked,[&](const QUrl& url)
    {
        ShellExecuteA(NULL, "open", url.toString().toStdString().c_str(), "", "", SW_SHOW);
    });
    if(bAbout)
    {
        showAbout();
    } else {
        showUsage();
    }
    //Ĭ�Ϲ�����������
    this->ui->textBrowser->moveCursor(QTextCursor::Start);
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::showAbout()
{
    this->setWindowTitle("���ڹ���");

    static const QDate buildDate = QLocale( QLocale::English ).toDate( QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");
    static const QTime buildTime = QTime::fromString(__TIME__, "hh:mm:ss");
    addText("����ʱ��",buildDate.toString("yyyy-MM-dd")+" "+buildTime.toString("hh:mm:ss"));
    addBlank();
    addBrief();
    addBlank();
    addAuthor();
}
void DialogHelp::showUsage()
{
    this->setWindowTitle("ʹ�ð���");
    addBrief();
    addBlank();
    addText("����Ŀ��","֧��ѡ���ļ��У�����Ŀ¼��֧���ֶ����루����Enter���������������������");
    addText("��������","����Ŀ¼���ų�Ŀ¼�������ļ����ų��ļ�����֧��·����");
    addText("�б�ѡ��","֧�ֵ�����˫����Ctrl��Shift��������");
    addText("ɾ������","֧���б�ѡ����ģ����б�ɾ��������ɾ������ɾ��������վ��");
    addText("�������","�����б��е�ȫ������ΪCSV�ļ�����ָ��Ŀ¼��");
    addText("�������","֧�ֶ��Ŀ�꣬��������Ĳ���������ʹ��Ӣ�ķֺ�[;]������");
    addBlank();
    addAuthor();
}

void DialogHelp::addText(const QString& flage, const QString& text)
{
    QString textInfo = flage;
    if(textInfo.isEmpty())
    {
        textInfo += text;
    }else {
        textInfo += "��";
        textInfo += "<font color='#5500ff' size='+1' face='Sans'>";
        textInfo += text;
        textInfo += "</font>";
    }
    this->ui->textBrowser->append(textInfo);
}

void DialogHelp::addUrl(const QString& flage, const QString& url)
{
    QString urlInfo = "<a href = \""+url+ "\">"+url+"</a>";
    this->ui->textBrowser->append(flage+ "��"+urlInfo);
}

void DialogHelp::addBlank()
{
    addText("","");
}
void DialogHelp::addBrief()
{
    addText("���߼��","Windows�ļ��������ߡ�֧��ָ��Ŀ¼���ļ����������ļ��������ļ����ݵĽ����������������������֧��ɾ���б�����ɾ����ɾ��������վ���͵���CSV������");
}

void DialogHelp::addAuthor()
{
    addUrl("Դ���ַ","https://github.com/deargo/FileSearch");
    addUrl("���͵�ַ","https://blog.csdn.net/aguoxin/article/details/104700809");
    addBlank();
    addText("��ϵ����","��ӭָ��bug������������ǰ���������ԡ�");
}
