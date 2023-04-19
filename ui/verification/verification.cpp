#include "verification.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QDebug>

#define VERIFICATION_DIGIT_NUM 5

Verification::Verification(QWidget *parent)
	: QWidget(parent), m_verificationCode(QString()), m_codeNum(VERIFICATION_DIGIT_NUM)
{
	qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
	m_verificationCode = getVerificationCodeByRand();
	m_colors = getColors();

	// m_updateTimer = new QTimer(this);
	// if (m_updateTimer)
	// {
	// 	connect(m_updateTimer, &QTimer::timeout, this, &Verification::sltTimerOut);
	// 	m_updateTimer->start(100);
	// }
}

Verification::~Verification()
{
}

void Verification::sltTimerOut()
{
	qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
	m_colors = getColors();
	update();
}

QString Verification::getVerificationCodeByRand()
{
	QString destCode = QString();
	for (int i = 0; i < m_codeNum; i++)
	{
		int flag = qrand() % 2;
		if (0 == flag)
		{
			int c = '0' + qrand() % 10;
			destCode += static_cast<QChar>(c);
		}
		else
		{
			int c = (qrand() % 2) ? 'a' : 'A';
			destCode += static_cast<QChar>(c + qrand() % 26);
		}
	}
	return destCode;
}

Qt::GlobalColor *Verification::getColors()
{
	static Qt::GlobalColor colors[VERIFICATION_DIGIT_NUM];
	for (int i = 0; i < m_codeNum; i++)
	{
		colors[i] = static_cast<Qt::GlobalColor>(2 + qrand() % 16);
	}
	return colors;
}

void Verification::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	// 填充验证码绘制矩形
	painter.fillRect(0, 0, 130, 30, QColor(255, 250, 240));
	painter.setFont(QFont("Comic Sans MS", 12));

	// 绘制验证码
	for (int i = 0; i < m_codeNum; i++)
	{
		painter.setPen(m_colors[i]);
		painter.drawText(25 * i, 0, 25, 30, Qt::AlignCenter, QString(m_verificationCode[i]));
	}
	// qInfo() << "paintEvent " << m_verificationCode;
	// 绘制噪点
	if (m_bstyle == BackgroundStyle::E_DOT)
		paintDot(&painter);
}

void Verification::paintDot(QPainter *painter)
{
	if (Q_NULLPTR == painter)
		return;

	for (int i = 0; i < 150; i++)
	{
		painter->setPen(m_colors[i % m_codeNum]);
		painter->drawPoint(qrand() % 129, qrand() % 29);
	}
}

void Verification::updateCode()
{
	m_verificationCode = getVerificationCodeByRand();
	m_colors = getColors();
	update();
	qInfo() << "verification code:" << m_verificationCode;
}

// void Verification::mouseDoubleClickEvent(QMouseEvent *event)
// {
// 	m_verificationCode = getVerificationCodeByRand();
// 	m_colors = getColors();
// 	update();
// 	QWidget::mouseDoubleClickEvent(event);
// }
