#include "gst/gst.h"
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>

static gboolean gst_test_init() {

    static int success = 0;
    if (!success) {
        GError* err = NULL;
        if (gst_init_check(NULL, NULL, &err)) {
            success = 1;
        }
        else {
            printf("Disabling GStreamer video support: %s\n", err->message);
            g_clear_error(&err);
            success = -1;
        }
    }
    return success > 0;

}
int main()
{   
    if (!gst_test_init()) {
        printf("GStreamer init failed!");
    }
    
    GstAppSrc* appsrc;
    GstAppSink* appsink;
    GError* err = NULL;
    char* desc = "filesrc location=test.h264 ! h264parse ! vaapih264dec ! autovideosink";
    printf("GStreamer pipeline: %s", desc);
    GstElement* pipeline = gst_parse_launch_full(desc, NULL, GST_PARSE_FLAG_FATAL_ERRORS, &err);
    if (!pipeline || err) {
        printf("GStreamer error: %s\n", err->message);
        g_clear_error(&err);
        if (pipeline) {
            gst_object_unref(pipeline);
        }
        return 0;
    }
    if (pipeline) {
        if (gst_element_set_state(pipeline, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
            printf("GStreamer pipeline create failure!\n");
        }
    }
	for (;;){
	}
    return 0;
}
