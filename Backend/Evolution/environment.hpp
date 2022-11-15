/** The creatures live in an environment which is a width x height grid cell.
 *  Each creatrue occupies one and only one grid cell.
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


class Environment
{
public:
    Environment(); // creates 30 x 30 grid
    Environment(int width, int height); // creates width x height grid
    int get_width();
    int get_height();
private:
    int width;
    int height;
};

#endif // ENVIRONMENT_H
