#ifndef EXPORTADVANCEDVIDEO_H
#define EXPORTADVANCEDVIDEO_H

#include <QDialog>

class ExportDialog;
class QComboBox;
class QLabel;
class QGridLayout;
class QCheckBox;

class ExportAdvancedVideo : public QDialog
{
	Q_OBJECT
public:
	ExportAdvancedVideo(ExportDialog* parent, int vcodec);
private slots:
	void save();

	// h264 functions
	void h264_encoder_change();
private:
	ExportDialog* ed;

	// h264 functions
	QComboBox* h264encoder;
	QComboBox* x264preset;
	QLabel* x264_preset_label;
	QWidget* x264_settings_widget;
	QCheckBox* x264_opencl_lookahead;
};

#endif // EXPORTADVANCEDVIDEO_H
