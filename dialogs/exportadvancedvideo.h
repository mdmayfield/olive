#ifndef EXPORTADVANCEDVIDEO_H
#define EXPORTADVANCEDVIDEO_H

#include <QDialog>

class ExportDialog;
class QComboBox;

class ExportAdvancedVideo : public QDialog
{
	Q_OBJECT
public:
	ExportAdvancedVideo(ExportDialog* parent, int vcodec);
private slots:
	void save();
private:
	ExportDialog* ed;
	QComboBox* x264preset;
};

#endif // EXPORTADVANCEDVIDEO_H
