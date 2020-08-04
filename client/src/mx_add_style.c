#include "uchat.h"

void mx_add_style(GtkWidget *widg, int type, t_user *s) {
    GtkStyleContext *context;
    GtkCssProvider *provider = gtk_css_provider_new();
    char *css = NULL;

    if (type == 1) {
        if (s->theme == 1)
            css = s->css_d;
        else
            css = s->css_l;
    }
    context = gtk_widget_get_style_context(widg);
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
        css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER (provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}
