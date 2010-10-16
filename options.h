#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
    class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Options *ui;

private slots:
    void on_btn_set_export_pc_clicked();
    void on_btn_set_load_pc_clicked();
    void on_btn_set_save_emu_clicked();
    void on_btn_set_save_pc_clicked();
};

#endif // OPTIONS_H