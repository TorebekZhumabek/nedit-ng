/*******************************************************************************
*                                                                              *
* highlightData.h -- Nirvana Editor Highlight Data Header File                 *
*                                                                              *
* Copyright 2003 The NEdit Developers                                          *
*                                                                              *
* This is free software; you can redistribute it and/or modify it under the    *
* terms of the GNU General Public License as published by the Free Software    *
* Foundation; either version 2 of the License, or (at your option) any later   *
* version. In addition, you may distribute versions of this program linked to  *
* Motif or Open Motif. See README for details.                                 *
*                                                                              *
* This software is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for    *
* more details.                                                                *
*                                                                              *
* You should have received a copy of the GNU General Public License along with *
* software; if not, write to the Free Software Foundation, Inc., 59 Temple     *
* Place, Suite 330, Boston, MA  02111-1307 USA                                 *
*                                                                              *
* Nirvana Text Editor                                                          *
* July 31, 2001                                                                *
*                                                                              *
*******************************************************************************/

#ifndef HIGHLIGHT_DATA_H_
#define HIGHLIGHT_DATA_H_

#include <QList>
#include <memory>

class PatternSet;
class QString;
class HighlightStyle;

bool LoadHighlightStringEx(const QString &string);
bool LoadStylesStringEx(const QString &string);
bool NamedStyleExists(const QString &styleName);
int FontOfNamedStyleIsBold(const QString &styleName);
int FontOfNamedStyleIsItalic(const QString &styleName);
int IndexOfNamedStyle(const QString &styleName);
PatternSet *FindPatternSet(const QString &langModeName);
QString BgColorOfNamedStyleEx(const QString &styleName);
QString ColorOfNamedStyleEx(const QString &styleName);
QString WriteHighlightStringEx();
QString WriteStylesStringEx();
void EditHighlightStyles(QWidget *parent, const QString &initialStyle);
void RenameHighlightPattern(const QString &oldName, const QString &newName);
std::unique_ptr<PatternSet> readDefaultPatternSet(const QString &langModeName);

// list of available highlight styles 
extern QList<HighlightStyle> HighlightStyles;
extern QList<PatternSet> PatternSets;

#endif
