#ifndef IMAGEBLOCK_H
#define IMAGEBLOCK_H

#include "core/block_data/BlockBase.h"

#include <QColor>


class ImageBlock : public BlockBase
{
    Q_OBJECT

    Q_PROPERTY(QString filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(double rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(bool shadow READ getShadow WRITE setShadow NOTIFY shadowChanged)

public:

    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Image";
        info.nameInUi = "Image";
        info.category << "General" << "Media + Presentation";
        info.availabilityRequirements << AvailabilityRequirement::LocalFileSelection;
        info.helpText = "Displays an image file.";
        info.qmlFile = "qrc:/qml/Blocks/Info/ImageBlock.qml";
        info.complete<ImageBlock>();
        return info;
    }

    explicit ImageBlock(MainController* controller, QString uid);

    virtual void getAdditionalState(QJsonObject& state) const override;
    virtual void setAdditionalState(const QJsonObject& state) override;

signals:
    void filePathChanged();
    void rotationChanged();
    void shadowChanged();

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    QString getFilePath() const { return m_filePath; }
    void setFilePath(const QString& value) { m_filePath = value; emit filePathChanged(); }

    double getRotation() const { return m_rotation; }
    void setRotation(double value) { m_rotation = value; emit rotationChanged(); }

    bool getShadow() const { return m_shadow; }
    void setShadow(bool value) { m_shadow = value; emit shadowChanged(); }

protected:
    QString m_filePath;
    double m_rotation;
    bool m_shadow;
};

#endif // IMAGEBLOCK_H
