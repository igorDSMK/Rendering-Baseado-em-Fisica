#include <ctime>
#include <iostream>
#include "main.h"

using namespace std;

int main(void)
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;


    /*OrthographicCamera camera{ -1.25f,
                                1.25f,
                               -1.25f,
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution },
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at


     */
     PinholeCamera camera{
        -3.25f,
        3.25f,
        -3.25f,
        3.25f,
        5.0f,
        glm::ivec2{x_resolution, y_resolution},
        glm::vec3{ 0.0f, -0.5f, -4.0f },  // position // sombra: 0.5f, -1.0f, -1.5f / padrao: 0.0f, -0.5f, -4.0f
        glm::vec3{0.0f, 1.0f, 0.0f},     // up
        glm::vec3{ 0.0f, -0.5f, 1.0f }}; // look at // sombra: 0.7f, 1.0f, 1.0f / padrao: 0.0f, -0.5f, 1.0f

    Scene scene{};
	int w;
	clock_t begin = clock();

    scene.load();

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    unsigned int maximum_depth = 5;
    RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer, maximum_depth );

    rt.integrate(); // Renders the final image.

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image.ppm" );

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << " segs\n";
	cin >> w;

    return EXIT_SUCCESS;
}

