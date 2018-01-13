#ifndef FILEITEM_H
#define FILEITEM_H

#include <QtCore>
#include <QDateTime>

class FileItem
{
public:
  FileItem(QString filePath, bool isDir, FileItem *parent = 0, int size = 0, QDateTime date = QDateTime::currentDateTime());

  QString getFilePath() const;
  void setFilePath(const QString &value);

  QDateTime getDate() const;
  void setDate(const QDateTime &value);

  QString getFileName() const;
  void setFileName(const QString &value);

  bool getFetched() const;
  void setFetched(bool value);

  bool getIsDir() const;
  void setIsDir(bool value);

  FileItem *getParent() const;

  QList<FileItem *> getChildList() const;
  void setChildList(const QList<FileItem *> &value);

  void addChild(FileItem *item);
  int childCount() const;
  int row() const;
  void setSize(int value);
  int getFileSizeInBytes() const;
  QString getFileSize() const; // human readable form

private:
  void setParent(FileItem *value);

  QString filePath;
  QString fileName;
  int size;
  QDateTime date;
  bool isDir;
  FileItem *parent;
  QList<FileItem *> childList;
  bool fetched; // А мы уже загружали child
};

#endif // FILEITEM_H
