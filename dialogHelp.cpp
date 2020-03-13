#include "dialogHelp.h"
#include "ui_dialogHelp.h"
#include <QDate>
#include <QTime>
#include <QUrl>
#include <QRect>
#include <QFile>
#include <QTextStream>
#include <windows.h>

DialogHelp::DialogHelp(QWidget *parent, Type type) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
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
    //������С����󴰿�
    QRect rect = parent->geometry();
    this->setMinimumSize(this->width(),this->height());
    this->setMaximumSize(rect.width()-20,rect.height()-20);

    //���ô���ֻ�йرհ�ť
    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag |= Qt::WindowCloseButtonHint;
    this->setWindowFlags(windowFlag);

    if(Type::ABOUT == type)
    {
        showAbout();
    } else if(Type::USAGE == type) {
        showUsage();
    } else {
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
    //��ֹ����
    this->setWindowTitle("ʹ�ð���");
    addBrief();
    addBlank();
    addText("����Ŀ��","֧��ѡ���ļ��У�����Ŀ¼��֧���ֶ����루����Enter���������������������");
    addText("��������","����Ŀ¼���ų�Ŀ¼�������ļ����ų��ļ�����֧��·�����ļ����ļ���������ʱ��֧�ִ�Сдƥ�䡢ȫ��ƥ���������ʽƥ��Ĺ���");
    addText("�б�ѡ��","֧�ֵ�����˫����Ctrl��Shift��������");
    addText("�б����","֧��Ctrl+C����·�����϶��п���ͷ���򡢱�ͷ˫������Ӧ�п�");
    addText("�б��Ҽ�","����·�����ļ����ԡ�������Ŀ¼��ɾ��ѡ��");
    addText("�б�ɾ��","֧���б�ѡ����ģ����б�ɾ��������ɾ������ɾ��������վ��");
    addText("�б���","�����б��е�ȫ������ΪCSV�ļ�����ָ��Ŀ¼��");
    addText("��������","֧�ֶ��Ŀ�꣬��������Ĳ���������ʹ��Ӣ�ķֺ�[;]������");
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
    addText("���߼��","Windows�ļ��������ߡ�֧��ָ��Ŀ¼���ļ����������ļ��������ļ����ݵĽ����������������������֧��ɾ���б�����ɾ����ɾ�������ա�����͵���CSV��������չʾ�б�֧�ֵ�����˫�����Ҽ��ͱ�ͷ���������");
}

void DialogHelp::addAuthor()
{
    addUrl("Դ���ַ","https://github.com/deargo/FileSearch");
    addUrl("���͵�ַ","https://blog.csdn.net/aguoxin/article/details/104700809");
    addBlank();
    addText("��ϵ����","��ӭָ��bug������������ǰ���������ԡ�");
}

