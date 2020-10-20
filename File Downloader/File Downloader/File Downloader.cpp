#include <stdio.h>

#include "libcurl/include/curl/curl.h"
#pragma comment(lib, "libcurl/lib/libcurl_a.lib")

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void download_file(const char* url)
{
	CURL* curl;
	FILE* fp;
	char output_file[FILENAME_MAX] = "downloaded_file.jpg";

	curl = curl_easy_init();
	if (curl)
	{
		fopen_s(&fp, output_file, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		CURLcode result = curl_easy_perform(curl);
		if (result != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(result));

		// Cleanup
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}


int main()
{
	download_file("https://cdn.vox-cdn.com/thumbor/uBibnxS6dKhINo467UYURu7QnGE=/0x0:3840x2160/920x613/filters:focal(1613x773:2227x1387):format(webp)/cdn.vox-cdn.com/uploads/chorus_image/image/61420935/BoJack_Horseman_S05E01_21m31s30960f.0.jpg");
}