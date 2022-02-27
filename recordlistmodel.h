#ifndef RECORDLISTMODEL_H
#define RECORDLISTMODEL_H

#include <QAbstractListModel>

class RecordListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RecordListModel(QObject *parent = nullptr);

    struct Record
    {
        QString name;
        int score;
    };

    public:
    void addRecord(const QString& name, int score);
    QString name(int row) const;
    int score(int row) const;

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual void sort(int column, Qt::SortOrder order);

private:
    QList<Record> m_datalist;
};

#endif // RECORDLISTMODEL_H
