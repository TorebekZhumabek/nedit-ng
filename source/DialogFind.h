
#ifndef DIALOG_FIND_H_
#define DIALOG_FIND_H_

#include "Dialog.h"
#include "Direction.h"
#include "SearchType.h"
#include "ui_DialogFind.h"

class DocumentWidget;
class MainWindow;

class DialogFind : public Dialog {
	Q_OBJECT
public:
    DialogFind(MainWindow *window, DocumentWidget *document, Qt::WindowFlags f = Qt::WindowFlags());
    ~DialogFind() override = default;
	
protected:
	void keyPressEvent(QKeyEvent *event) override;
	void showEvent(QShowEvent *event) override;

public:
    void setDocument(DocumentWidget *document);
    void setTextField(DocumentWidget *document);
	void initToggleButtons(SearchType searchType);
	void fUpdateActionButtons();
	
private:
    bool getFindDlogInfoEx(Direction *direction, QString *searchString, SearchType *searchType);
	
public:
	bool keepDialog() const;
	
private Q_SLOTS:
	void on_checkBackward_toggled(bool checked);
	void on_checkRegex_toggled(bool checked);
	void on_checkCase_toggled(bool checked);
	void on_checkKeep_toggled(bool checked);
	void on_textFind_textChanged(const QString &text);
	void on_buttonFind_clicked();
	
public:
    MainWindow *window_;
    DocumentWidget *document_;	
    bool lastRegexCase_;   // idem, for regex mode in find dialog
    bool lastLiteralCase_; // idem, for literal mode
    Ui::DialogFind ui;
};


#endif
