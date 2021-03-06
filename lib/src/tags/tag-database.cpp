#include "tag-database.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include "tag-type.h"


TagDatabase::TagDatabase(QString typeFile)
	: m_typeFile(std::move(typeFile))
{}

bool TagDatabase::load()
{
	loadTypes();
	return true;
}

void TagDatabase::loadTypes()
{
	if (!m_tagTypes.isEmpty())
		return;

	QFile f(m_typeFile);
	if (!f.open(QFile::ReadOnly | QFile::Text))
		return;

	QTextStream in(&f);
	while (!in.atEnd())
	{
		QString line = in.readLine();

		QStringList data = line.split(',');
		if (data.count() != 2)
			continue;

		m_tagTypes.insert(data[0].toInt(), TagType(data[1]));
	}
	f.close();
}

const QMap<int, TagType> &TagDatabase::tagTypes() const
{
	return m_tagTypes;
}
