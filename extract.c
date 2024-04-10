#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

char search_query[1024];
CURL *curl;
CURLcode res;

int get_user_input() {
    printf("Busca: ");
    if (fgets(search_query, sizeof(search_query), stdin) == NULL) {
        fprintf(stderr, "Erro ao ler a entrada\n");
        return 1;
    }
    search_query[strcspn(search_query, "\n")] = '\0'; 
    return 0;
}

char *build_url(char *search_query) {
    int query_len = strlen(search_query);
    char *url = malloc(strlen(GOOGLE_SEARCH_BASE_URL) + query_len + strlen(GOOGLE_IMAGE_SEARCH_PARAM) + 1);
    if (url == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a URL\n");
        return NULL;
    }
    strcpy(url, GOOGLE_SEARCH_BASE_URL);
    strcat(url, search_query);
    strcat(url, GOOGLE_IMAGE_SEARCH_PARAM);
    return url;
}

char *fetch_data(char *url) {
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); 
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return NULL; 
    }
    return NULL;
}

char *extract_image_url(char *data) {
    return NULL; 
}

int download_image(char *image_url, char *filename) {
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, image_url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fopen(filename, "wb"));
        res = curl_easy_perform(curl);
        /* Tratar erros com base em res */
        curl_easy_cleanup(curl);
        return 0; 
    }
    return 1;
}

int main() {
    if (get_user_input()) {
        return 1;
    }
    char *url = build_url(search_query);
    if (url == NULL) {
        return 1;
    }
    fetch_data(url);
    free(url);


    char *image_url = extract_image_url(data);
    if (image_url != NULL) {
        if (download_image(image_url, "imagem.png")) {
            fprintf(stderr, "Erro ao baixar a imagem\n");
            return 1;
        }
        printf("Imagem salva em imagem.png\n");
    } else {
        fprintf(stderr, "Erro ao extrair a URL da imagem\n");
    }

    return 0;
}
