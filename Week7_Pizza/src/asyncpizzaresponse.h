#ifndef ASYNCPIZZARESPONSE_H
#define ASYNCPIZZARESPONSE_H

#include <QQuickImageResponse>
#include <QRunnable>
#include <QStringList>
#include <QMap>
#include <QPainter>
/*******************************************************
 * Building a one-time-run PizzaRenderer!
 *
 *  Idea -
 *      1.)Render Pizza in a 523,528 (pizza size) QImage
 *      2.)For each topping in the topping list, load and
 *          paint the toppings.
 *
 *
 * *****************************************************/
class AsyncPizzaResponse : public QQuickImageResponse, public QRunnable
{
    public:
        AsyncPizzaResponse(const QStringList &toppings, const QMap<QString,QImage *> &loadedImages, const QSize &requestedSize)
         : m_toppingsList(toppings), m_loadedImages(loadedImages), m_requestedSize(requestedSize), m_texture(0)
        {
            setAutoDelete(false);
        }

        QQuickTextureFactory *textureFactory() const
        {
            return m_texture;
        }

        // Create draw functions for each topping - Remember the pizza dimensions
        void drawPepperoni(QPainter &painter)
        {
            QImage  pepperonis(95,95,QImage::Format_RGB32);
            pepperonis = (*m_loadedImages.value("pepperonis"));
            int x = 92;
            int y = 78;
            int columns_drawn(0);
            painter.drawImage(80,175,pepperonis);
            for(int index(0); index < 16; index++)
            {
                painter.drawImage(x,y,pepperonis);
                x+= 80;
                columns_drawn++;
                if(columns_drawn >= 4)
                {
                    columns_drawn = 0;
                    x = 92 - ((10 - index)*4);
                    y+= 92;
                }
            }
            painter.drawImage(385,175,pepperonis);
            painter.drawImage(385,245,pepperonis);
        }

        void drawAnchovies(QPainter &painter)
        {
            QImage  anchovies(95,95,QImage::Format_RGB32);
            anchovies = (*m_loadedImages.value("anchovies"));
            int x = 92;
            int y = 78;
            int columns_drawn(0);
            painter.drawImage(80,175,anchovies);
            for(int index(0); index < 16; index++)
            {
                painter.drawImage(x,y,anchovies);
                x+= 80;
                columns_drawn++;
                if(columns_drawn >= 4)
                {
                    columns_drawn = 0;
                    x = 92 - ((10 - index)*4);
                    y+= 92;
                }
            }
            painter.drawImage(385,175,anchovies);
            painter.drawImage(385,245,anchovies);
        }
        void drawPineapple(QPainter &painter)
        {
            QImage  pineapple(95,95,QImage::Format_RGB32);
            pineapple = (*m_loadedImages.value("pineapple"));
            int x = 92;
            int y = 78;
            int columns_drawn(0);
            painter.drawImage(80,175,pineapple);
            for(int index(0); index < 16; index++)
            {
                painter.drawImage(x,y,pineapple);
                x+= 83;
                columns_drawn++;
                if(columns_drawn >= 4)
                {
                    columns_drawn = 0;
                    x = 92 - ((10 - index)*4);
                    y+= 95;
                }
            }
            painter.drawImage(385,175,pineapple);
            painter.drawImage(385,245,pineapple);
        }
        void drawTomatoes(QPainter &painter)
        {
            QImage  tomatoes(95,95,QImage::Format_RGB32);
            tomatoes = (*m_loadedImages.value("tomatoes"));
            int x = 92;
            int y = 78;
            int columns_drawn(0);
            painter.drawImage(80,175,tomatoes);
            for(int index(0); index < 16; index++)
            {
                painter.drawImage(x,y,tomatoes);
                x+= 83;
                columns_drawn++;
                if(columns_drawn >= 4)
                {
                    columns_drawn = 0;
                    x = 92 - ((10 - index)*4);
                    y+= 95;
                }
            }
            painter.drawImage(385,175,tomatoes);
            painter.drawImage(385,245,tomatoes);
        }
        void drawPeppers(QPainter &painter)
        {
            QImage  tomatoes(95,95,QImage::Format_RGB32);
            tomatoes = (*m_loadedImages.value("peppers"));
            int x = 92;
            int y = 78;
            int columns_drawn(0);
            painter.drawImage(80,175,tomatoes);
            for(int index(0); index < 16; index++)
            {
                painter.drawImage(x,y,tomatoes);
                x+= 83;
                columns_drawn++;
                if(columns_drawn >= 4)
                {
                    columns_drawn = 0;
                    x = 92 - ((10 - index)*4);
                    y+= 95;
                }
            }
            painter.drawImage(385,175,tomatoes);
            painter.drawImage(385,245,tomatoes);
        }


        void run()
        {
            QImage image(523, 528, QImage::Format_RGB32);
            image = (*m_loadedImages.value("pizza"));

            // Create the painter
            QPainter  painter(&image);

            // check toppings and draw all toppings in list
            if(m_toppingsList.contains("Pepperoni"))
                drawPepperoni(painter);
            if(m_toppingsList.contains("Anchovies"))
                drawAnchovies(painter);
            if(m_toppingsList.contains("Pineapple"))
                drawPineapple(painter);
            if(m_toppingsList.contains("Tomatoes"))
                drawTomatoes(painter);
            if(m_toppingsList.contains("Peppers"))
                drawPeppers(painter);

            // ignore this stuff
            if (m_requestedSize.isValid() && (image.size() != m_requestedSize))
                image = image.scaled(m_requestedSize);
            m_texture = QQuickTextureFactory::textureFactoryForImage(image);
            emit finished();
        }

        QMap<QString,QImage *> m_loadedImages;
        QStringList m_toppingsList;
        QSize m_requestedSize;
        QQuickTextureFactory *m_texture;
};

#endif // ASYNCPIZZARESPONSE_H
