#include <hpdf.h>
#include <iostream>

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    std::cerr << "Error: " << error_no << ", detail: " << detail_no << std::endl;
}

int main() {
    // Create a new PDF document
    HPDF_Doc pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
        std::cerr << "Error: Cannot create PDF object" << std::endl;
        return 1;
    }

    // Add a new page
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Set font and text size
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 24);

    // Write text to the page
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 50, 750, "Hello World!");
    HPDF_Page_EndText(page);

    // Save the document to a file
    HPDF_SaveToFile(pdf, "examplePDF.pdf");

    // Clean up
    HPDF_Free(pdf);

    std::cout << "PDF created successfully!" << std::endl;
    return 0;
}

