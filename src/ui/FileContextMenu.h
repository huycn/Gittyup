//
//          Copyright (c) 2016, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Jason Haslam
//

#ifndef FILECONTEXTMENU_H
#define FILECONTEXTMENU_H

#include "git/Id.h"
#include "git/Index.h"
#include "git/Commit.h"
#include <QMenu>

class ExternalTool;
class RepoView;

class FileContextMenu : public QMenu {
  Q_OBJECT

public:
  FileContextMenu(RepoView *view, const QStringList &files,
                  const git::Index &index = git::Index(),
                  QWidget *parent = nullptr, bool staged = false);

  QAction *doubleClickAction() { return mDoubleClickAction; }

private slots:
  void ignoreFile();

private:
  QAction *addExternalToolsAction(const QList<ExternalTool *> &tools);
  bool exportFile(const RepoView *view, const QString &folder,
                  const QString &file);
  /*!
   * \param staged When true, "Discard Changes" resets the staged files back
   * to HEAD (leaving the working directory untouched); when false, it
   * resets the working directory to match the index (leaving staged
   * changes untouched).
   */
  void handleUncommittedChanges(const git::Index &index,
                                const QStringList &files, bool staged);
  void handleCommits(const QList<git::Commit> &commits,
                     const QStringList &files);

  RepoView *mView;
  QStringList mFiles;
  QAction *mDoubleClickAction;

  friend class TestTreeView;
};

#endif
