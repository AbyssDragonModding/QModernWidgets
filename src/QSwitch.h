// C++ implementation of QSwitch, based off IOS switch, originally prototyped with PySide6

#pragma once
// QT Framework Includes
#include <QWidget>
#include <QRect>
#include <QProperty>
#include <QColor>
#include <QCheckBox>
#include <QSize>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

namespace QModern
{
    class QSwitch : public QCheckBox
    {
        Q_OBJECT
        Q_PROPERTY(QColor activeColor READ _getActiveColor WRITE setActiveColor NOTIFY activeColorChanged FINAL);
        Q_PROPERTY(QColor knobColor READ _getKnobColor WRITE setKnobColor NOTIFY knobColorChanged FINAL);
        Q_PROPERTY(QColor backgroundColor READ _getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)
    // Public methods
    public:
        explicit QSwitch(QWidget *parent = nullptr, int height = 20);
        ~QSwitch();
        //
        // Event overloads
        //
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void paintEvent(QPaintEvent *event) override;

        //
        //setters
        //

        // Set QSwitches "Active" (true) color
        void setActiveColor(QColor newColor);

        // Set QSwitch "background" (false) color
        void setBackgroundColor(QColor newColor);

        // Set QSwitch knob color
        void setKnobColor(QColor newColor);

         // sets the new height of QSwitch, updates associated variables, and calculates width based off height
        void setHeight(int newHeight);

        // Enable drop shadow for QSwitch
        void enableDropShadow(bool newState);

        //
        // Getters
        //

        // Get the *parent widget of the QSwitch
        QWidget *getParent() const;
    // Private methods
    private:
        // Calls the update() and repaint() functions for the widget
        void _repaintWidget();

        //
        // Getters
        //

        // Get the active color of QSwitch as QColor
        QColor _getActiveColor() const;

        // Get the background color of QSwitch as QColor
        QColor _getBackgroundColor() const;

        // Get the Knob color of QSwitch as QColor
        QColor _getKnobColor() const;

    signals:
        void activeColorChanged();
        void knobColorChanged();
        void backgroundColorChanged();

    private:
        QWidget *m_parent; // used if needed for other functions
        QSize m_widgetSize;
        int m_knobPadding;
        QRect m_widgetBounds;
        bool m_hasDropShadow;

        // Switch colors
        QColor m_activeColor;
        QColor m_knobColor;
        QColor m_backgroundColor;
    };
}
