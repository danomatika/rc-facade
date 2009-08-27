
#include "FacadeSample.h"

std::vector<Color> FacadeSample::colors;
Color FacadeSample::background;
FrameBuffer FacadeSample::frame("192.168.5.59", 8080);
Building FacadeSample::building;

void FacadeSample::walkColors()
{
    LOG << "num colors; " << colors.size() << std::endl;
    for(unsigned int i = 0; i < colors.size(); ++i)
    {
        LOG << "Set building to " << colors[i] << std::endl;
        frame.setColor(colors[i]);
        frame.flush();
        usleep(100000);
    }
    frame.setColor(background);
}

void FacadeSample::walkSides()
{
    std::vector<Side*>& sides = building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        frame.setColor(background);
        for(unsigned int i; i < colors.size(); ++i)
        {
            LOG << "Set " << sides[i]->getName() << " to " << colors[i] << std::endl;
            sides[i]->setColor(frame, colors[i]);
            frame.flush();
            usleep(100000);
        }
    }
}

void FacadeSample::walkRows()
{
    for(unsigned int i = 0; i < colors.size(); ++i)
    {
        for(int row = 0; row < building.getNrRows(); row++)
        {
            LOG << "Set row " << row << " to " << colors[i] << std::endl;
            frame.setColor(background);

            std::vector<Side*>& sides = building.getSides();
            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                sides[i]->setRowColor(frame, row, colors[i]);
            }
            frame.flush();
            usleep(100000);
        }
    }
}

void FacadeSample::walkColumns()
{
    for(unsigned int i = 0; i < colors.size(); ++i)
    {
        for(int column = 0; column < building.getNrCols(); column++)
        {
            LOG << "Set column " << column << " to " << colors[i] << std::endl;
            frame.setColor(background);

            std::vector<Side*>& sides = building.getSides();
            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                sides[i]->setColumnColor(frame, column, colors[i]);
            }
            frame.flush();
            usleep(100000);
        }
    }
}

void FacadeSample::main()
{
    LOG << "Facade Sample" << std::endl;

    colors.push_back(Color(255, 0,   0,   255));
    colors.push_back(Color(0,   255, 0,   255));
    colors.push_back(Color(0,   0,   255, 255));
    colors.push_back(Color(255, 255, 0,   255));
    colors.push_back(Color(255, 0,   255, 255));
    colors.push_back(Color(0,   255, 255, 255));
    colors.push_back(Color(127, 127, 127, 255));
    colors.push_back(Color(255, 127, 127, 255));

    background.set(0, 0, 0);

    walkColors();
    sleep(1);
    walkSides();
    sleep(1);
    walkRows();
    sleep(1);
    walkColumns();
    sleep(1);

    frame.setColor(background);
    frame.flush();
}
