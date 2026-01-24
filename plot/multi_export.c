#include "multi_export.h"

#include <stdio.h>

int write_row(FILE* file, const SinglePlot* plots, const int plot_count, const int row) {
    int bytes_written = 0;
    for (int plot_i = 0; plot_i < plot_count; ++plot_i) {
        if (plot_i) {
            bytes_written += fprintf(file, ",");
        }
        const Vector2* data = plots[plot_i].data_source.data;
        const int data_count = plots[plot_i].data_source.count;

        if (row >= data_count) {
            bytes_written += fprintf(file, ",");
        }
        else {
            bytes_written += fprintf(file, "%f,%f", data[row].x, data[row].y);
        }
    }
    bytes_written += fprintf(file, "\r\n");
    return bytes_written;
}

int multi_export(const SinglePlot* plots, const int plot_count) {
    const char csv_name[] = "sigma_epsilon.csv";
    FILE* file = fopen(csv_name, "w");
    printf("Exporting to %s\n", csv_name);

    if (!file) {
        puts("Cannot open file");
        return 0;
    }

    int bytes_written = fprintf(file, "sigma-epsilon\r\n%s,%s\r\n", "aa", "bb");
    int longest_plot = 0;
    for (int i = 0; i < plot_count; ++i) {
        if (i) {
            bytes_written += fprintf(file, ",");
        }
        bytes_written += fprintf(file, "%d-x,%d-y", i, i);
        if (plots[i].data_source.count > longest_plot) longest_plot = plots[i].data_source.count;
    }
    bytes_written += fprintf(file, "\r\n");

    for (int i = 0; i < longest_plot; ++i) {
        bytes_written += write_row(file, plots, plot_count, i);
    }
    fclose(file);
    return bytes_written;
}
