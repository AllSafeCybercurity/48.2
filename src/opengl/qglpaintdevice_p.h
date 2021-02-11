/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGLPAINTDEVICE_P_H
#define QGLPAINTDEVICE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QtOpenGL module.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//


#include <qpaintdevice.h>
#include <qgl.h>


QT_BEGIN_NAMESPACE

class Q_OPENGL_EXPORT QGLPaintDevice : public QPaintDevice
{
public:
    QGLPaintDevice();
    virtual ~QGLPaintDevice();

    int devType() const {return QInternal::OpenGL;}

    virtual void beginPaint();
    virtual void ensureActiveTarget();
    virtual void endPaint();

    virtual QGLContext* context() const = 0;
    virtual QGLFormat format() const;
    virtual QSize size() const = 0;
    virtual bool alphaRequested() const;
    virtual bool isFlipped() const;

    // returns the QGLPaintDevice for the given QPaintDevice
    static QGLPaintDevice* getDevice(QPaintDevice*);

protected:
    int metric(QPaintDevice::PaintDeviceMetric metric) const;
    GLuint m_previousFBO;
    GLuint m_thisFBO;
};


// Wraps a QGLWidget
class QGLWidget;
class QGLWidgetGLPaintDevice : public QGLPaintDevice
{
public:
    QGLWidgetGLPaintDevice();

    virtual QPaintEngine* paintEngine() const;

    // QGLWidgets need to do swapBufers in endPaint:
    virtual void beginPaint();
    virtual void endPaint();
    virtual QSize size() const;
    virtual QGLContext* context() const;

    void setWidget(QGLWidget*);

private:
    friend class QGLWidget;
    QGLWidget *glWidget;
};

QT_END_NAMESPACE

#endif // QGLPAINTDEVICE_P_H
