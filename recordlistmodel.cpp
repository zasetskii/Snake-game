#include "recordlistmodel.h"
#include <QDebug>

RecordListModel::RecordListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

void RecordListModel::addRecord(const QString &name, int score)
{
    beginInsertRows(QModelIndex(), m_datalist.count(), m_datalist.count());
    m_datalist.append({name, score});
    endInsertRows();
}

QString RecordListModel::name(int row) const
{
    return m_datalist.at(row).name;
}

int RecordListModel::score(int row) const
{
    return m_datalist.at(row).score;
}

int RecordListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_datalist.count();
}

int RecordListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant RecordListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        Record record = m_datalist.at(index.row());
        if (index.column() == 0)
            return record.name;
        else
            return record.score;
    }
    else
        return QVariant();
}

void RecordListModel::sort(int column, Qt::SortOrder order)
{
    Q_UNUSED(column)
    if (order == Qt::AscendingOrder)
    {
        std::sort(m_datalist.begin(), m_datalist.end(),
                  [](const Record& r1, const Record& r2) -> bool { return r1.score < r2.score; });
    }
    else
    {
        std::sort(m_datalist.begin(), m_datalist.end(),
                  [](const Record& r1, const Record& r2) -> bool { return r1.score > r2.score; });
    }
}
