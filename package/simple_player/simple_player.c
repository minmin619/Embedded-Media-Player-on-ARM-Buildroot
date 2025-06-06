#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline;
    GMainLoop *loop;

    // Initialize the GStreamer system
    gst_init(&argc, &argv);

    // Check if the correct number of arguments is provided (expects a video file path)
    if (argc != 2) {
        g_printerr("Usage: %s <video file path>\n", argv[0]);
        return -1;
    }

    // Create the playbin element, a high-level playback element that handles decoding, audio/video output, etc.
    pipeline = gst_element_factory_make("playbin", "player");
    if (!pipeline) {
        g_printerr("Failed to create GStreamer playbin element\n");
        return -1;
    }

    // Set the video source using a URI format (file path in this case)
    g_object_set(pipeline, "uri", g_strdup_printf("file://%s", argv[1]), NULL);

    // Create the main event loop to handle playback events
    loop = g_main_loop_new(NULL, FALSE);

    // Set the pipeline state to PLAYING to start video playback
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_print("Now playing: %s\n", argv[1]);

    // Run the main loop until playback ends or is manually stopped
    g_main_loop_run(loop);

    // After playback finishes, stop the pipeline and free resources
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    return 0;
}

