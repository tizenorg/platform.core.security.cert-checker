/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/*
 * @file        test_certs.cpp
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       Tests of certs class (signatures, certificates, OCSP)
 */

#include <boost/test/unit_test.hpp>
#include <string>
#include <thread>

#include <cchecker/log.h>
#include <certs_.h>
#include <app_event_operators.h>

using namespace CCHECKER;

BOOST_FIXTURE_TEST_SUITE(CERT_TEST, Certs_)

BOOST_AUTO_TEST_CASE(Certs_OCSP_positive) {

    //*.wikipedia.com:
    chain_t chain = {
            "MIIH1jCCBr6gAwIBAgISESGXLjKl5bLinUct/tty1iduMA0GCSqGSIb3DQEBCwUA\
MGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYD\
VQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hB\
MjU2IC0gRzIwHhcNMTQxMjE2MjEyNDAzWhcNMTcwMjE5MTIwMDAwWjB5MQswCQYD\
VQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNU2FuIEZyYW5j\
aXNjbzEjMCEGA1UEChMaV2lraW1lZGlhIEZvdW5kYXRpb24sIEluYy4xGDAWBgNV\
BAMMDyoud2lraXBlZGlhLm9yZzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\
ggEBAMH1s5FRkOrf7p3fQNqqKbre0J/7w3isYDt/tRZw4bHm7mI73Y5335iwulvr\
Bmsq93RSMHizLx8J0RdkKcfitWS/o0kIKP1wehDzHOerH6s1e7Z3j/uI6mMzDZMs\
EWDnPA21kwqtXEIwYEAj+tRU832j3CeJ3pMCE75uE+lnN0hVJIXd2c0/hnPRAWTV\
ENV6FQGCy1zwowlndvFTALQ+4LSCNtZnwVtSecgKVPAO/WkLMk2OdLB6UITT1wPN\
iP2qzm2uFWetO/MzN6paOiS2DqXFp4r7KZTSNOl3CTn8MufKGPqA0ajJJDLSX0/K\
DmC1Sw6ndBerUuRDSaDeEq2I8HMCAwEAAaOCBGkwggRlMA4GA1UdDwEB/wQEAwIF\
oDBJBgNVHSAEQjBAMD4GBmeBDAECAjA0MDIGCCsGAQUFBwIBFiZodHRwczovL3d3\
dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzCCAq4GA1UdEQSCAqUwggKhgg8q\
Lndpa2lwZWRpYS5vcmeCDyoubWVkaWF3aWtpLm9yZ4IPKi53aWtpYm9va3Mub3Jn\
gg4qLndpa2lkYXRhLm9yZ4IPKi53aWtpbWVkaWEub3JnghkqLndpa2ltZWRpYWZv\
dW5kYXRpb24ub3Jngg4qLndpa2luZXdzLm9yZ4IPKi53aWtpcXVvdGUub3JnghAq\
Lndpa2lzb3VyY2Uub3JnghEqLndpa2l2ZXJzaXR5Lm9yZ4IQKi53aWtpdm95YWdl\
Lm9yZ4IQKi53aWt0aW9uYXJ5Lm9yZ4IRKi5tLm1lZGlhd2lraS5vcmeCESoubS53\
aWtpcGVkaWEub3JnghEqLm0ud2lraWJvb2tzLm9yZ4IQKi5tLndpa2lkYXRhLm9y\
Z4IRKi5tLndpa2ltZWRpYS5vcmeCGyoubS53aWtpbWVkaWFmb3VuZGF0aW9uLm9y\
Z4IQKi5tLndpa2luZXdzLm9yZ4IRKi5tLndpa2lxdW90ZS5vcmeCEioubS53aWtp\
c291cmNlLm9yZ4ITKi5tLndpa2l2ZXJzaXR5Lm9yZ4ISKi5tLndpa2l2b3lhZ2Uu\
b3JnghIqLm0ud2lrdGlvbmFyeS5vcmeCFCouemVyby53aWtpcGVkaWEub3Jngg1t\
ZWRpYXdpa2kub3Jngg13aWtpYm9va3Mub3Jnggx3aWtpZGF0YS5vcmeCDXdpa2lt\
ZWRpYS5vcmeCF3dpa2ltZWRpYWZvdW5kYXRpb24ub3Jnggx3aWtpbmV3cy5vcmeC\
DXdpa2lxdW90ZS5vcmeCDndpa2lzb3VyY2Uub3Jngg93aWtpdmVyc2l0eS5vcmeC\
Dndpa2l2b3lhZ2Uub3Jngg53aWt0aW9uYXJ5Lm9yZ4INd2lraXBlZGlhLm9yZzAJ\
BgNVHRMEAjAAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjBJBgNVHR8E\
QjBAMD6gPKA6hjhodHRwOi8vY3JsLmdsb2JhbHNpZ24uY29tL2dzL2dzb3JnYW5p\
emF0aW9udmFsc2hhMmcyLmNybDCBoAYIKwYBBQUHAQEEgZMwgZAwTQYIKwYBBQUH\
MAKGQWh0dHA6Ly9zZWN1cmUuZ2xvYmFsc2lnbi5jb20vY2FjZXJ0L2dzb3JnYW5p\
emF0aW9udmFsc2hhMmcycjEuY3J0MD8GCCsGAQUFBzABhjNodHRwOi8vb2NzcDIu\
Z2xvYmFsc2lnbi5jb20vZ3Nvcmdhbml6YXRpb252YWxzaGEyZzIwHQYDVR0OBBYE\
FPijzqMJdm7bqDx4SGOcGUzAx0qdMB8GA1UdIwQYMBaAFJbeYfG9HBYpUxzAzH07\
gwBA5hp8MA0GCSqGSIb3DQEBCwUAA4IBAQC45+nGVISGOZctc9mxhil3EDmlBIzY\
5mQJ+APT5oUGthZfe6v9lP7yRLIEhHMDl72Jrnzzx3ksUnAqJTOcsnuzQvZq45pn\
gOk/sO6ilkOun/u5QBigxne1/P4g2SYkISqRqA0Z9FloEd6odDb6dbIHhhz270rH\
3pjewMLq6OA09eklPav4f3NiBL/VcqG53TRTJW6eHxZuEsGAgBmwk6jKf8e+BjmZ\
4V9POUs5kH7d1OJs9d5Fv9y3t/Yt1pGaHyK/DTUbYVhMyn0EaLxd3FLJ9ABKpQJ+\
OUcTfe55U2Ox1H/87b6Ca04DDl3u2i87jPbhgshWSNwU8+llHCst0sbG",

"MIIEaTCCA1GgAwIBAgILBAAAAAABRE7wQkcwDQYJKoZIhvcNAQELBQAwVzELMAkG\
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw0xNDAyMjAxMDAw\
MDBaFw0yNDAyMjAxMDAwMDBaMGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\
YWxTaWduIG52LXNhMTwwOgYDVQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBW\
YWxpZGF0aW9uIENBIC0gU0hBMjU2IC0gRzIwggEiMA0GCSqGSIb3DQEBAQUAA4IB\
DwAwggEKAoIBAQDHDmw/I5N/zHClnSDDDlM/fsBOwphJykfVI+8DNIV0yKMCLkZc\
C33JiJ1Pi/D4nGyMVTXbv/Kz6vvjVudKRtkTIso21ZvBqOOWQ5PyDLzm+ebomchj\
SHh/VzZpGhkdWtHUfcKc1H/hgBKueuqI6lfYygoKOhJJomIZeg0k9zfrtHOSewUj\
mxK1zusp36QUArkBpdSmnENkiN74fv7j9R7l/tyjqORmMdlMJekYuYlZCa7pnRxt\
Nw9KHjUgKOKv1CGLAcRFrW4rY6uSa2EKTSDtc7p8zv4WtdufgPDWi2zZCHlKT3hl\
2pK8vjX5s8T5J4BO/5ZS5gIg4Qdz6V0rvbLxAgMBAAGjggElMIIBITAOBgNVHQ8B\
Af8EBAMCAQYwEgYDVR0TAQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQUlt5h8b0cFilT\
HMDMfTuDAEDmGnwwRwYDVR0gBEAwPjA8BgRVHSAAMDQwMgYIKwYBBQUHAgEWJmh0\
dHBzOi8vd3d3Lmdsb2JhbHNpZ24uY29tL3JlcG9zaXRvcnkvMDMGA1UdHwQsMCow\
KKAmoCSGImh0dHA6Ly9jcmwuZ2xvYmFsc2lnbi5uZXQvcm9vdC5jcmwwPQYIKwYB\
BQUHAQEEMTAvMC0GCCsGAQUFBzABhiFodHRwOi8vb2NzcC5nbG9iYWxzaWduLmNv\
bS9yb290cjEwHwYDVR0jBBgwFoAUYHtmGkUNl8qJUC99BM00qP/8/UswDQYJKoZI\
hvcNAQELBQADggEBAEYq7l69rgFgNzERhnF0tkZJyBAW/i9iIxerH4f4gu3K3w4s\
32R1juUYcqeMOovJrKV3UPfvnqTgoI8UV6MqX+x+bRDmuo2wCId2Dkyy2VG7EQLy\
XN0cvfNVlg/UBsD84iOKJHDTu/B5GqdhcIOKrwbFINihY9Bsrk8y1658GEV1BSl3\
30JAZGSGvip2CTFvHST0mdCF/vIhCPnG9vHQWe3WVjwIKANnuvD58ZAWR65n5ryA\
SOlCdjSXVWkkDoPWoC209fN5ikkodBpBocLTJIg1MGCUF7ThBCIxPTsvFwayuJ2G\
K1pp74P1S8SqtCr4fKGxhZSM9AyHDPSsQPhZSZg=",

"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\
MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\
YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\
aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\
jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\
xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\
1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\
snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\
U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\
9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\
BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\
AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\
yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\
38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\
AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\
DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\
HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A=="};

    Certs::ocsp_response_t resp = check_ocsp_chain_ (chain);
    LogDebug("Certs_::check_ocsp_chain_ response : " << (int) resp);
    BOOST_REQUIRE(resp == Certs::ocsp_response_t::OCSP_CHECK_AGAIN);
}

BOOST_AUTO_TEST_CASE(Certs_OCSP_negative_1) {
    // Broken chain of certificates

    //*.wikipedia.com:
   chain_t chain = {
            "MIIH1jCCBr6gAwIBAgISESGXLjKl5bLinUct/tty1iduMA0GCSqGSIb3DQEBCwUA\
MGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYD\
VQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hB\
MjU2IC0gRzIwHhcNMTQxMjE2MjEyNDAzWhcNMTcwMjE5MTIwMDAwWjB5MQswCQYD\
VQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNU2FuIEZyYW5j\
aXNjbzEjMCEGA1UEChMaV2lraW1lZGlhIEZvdW5kYXRpb24sIEluYy4xGDAWBgNV\
BAMMDyoud2lraXBlZGlhLm9yZzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\
ggEBAMH1s5FRkOrf7p3fQNqqKbre0J/7w3isYDt/tRZw4bHm7mI73Y5335iwulvr\
Bmsq93RSMHizLx8J0RdkKcfitWS/o0kIKP1wehDzHOerH6s1e7Z3j/uI6mMzDZMs\
EWDnPA21kwqtXEIwYEAj+tRU832j3CeJ3pMCE75uE+lnN0hVJIXd2c0/hnPRAWTV\
ENV6FQGCy1zwowlndvFTALQ+4LSCNtZnwVtSecgKVPAO/WkLMk2OdLB6UITT1wPN\
iP2qzm2uFWetO/MzN6paOiS2DqXFp4r7KZTSNOl3CTn8MufKGPqA0ajJJDLSX0/K\
DmC1Sw6ndBerUuRDSaDeEq2I8HMCAwEAAaOCBGkwggRlMA4GA1UdDwEB/wQEAwIF\
oDBJBgNVHSAEQjBAMD4GBmeBDAECAjA0MDIGCCsGAQUFBwIBFiZodHRwczovL3d3\
dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzCCAq4GA1UdEQSCAqUwggKhgg8q\
Lndpa2lwZWRpYS5vcmeCDyoubWVkaWF3aWtpLm9yZ4IPKi53aWtpYm9va3Mub3Jn\
gg4qLndpa2lkYXRhLm9yZ4IPKi53aWtpbWVkaWEub3JnghkqLndpa2ltZWRpYWZv\
dW5kYXRpb24ub3Jngg4qLndpa2luZXdzLm9yZ4IPKi53aWtpcXVvdGUub3JnghAq\
Lndpa2lzb3VyY2Uub3JnghEqLndpa2l2ZXJzaXR5Lm9yZ4IQKi53aWtpdm95YWdl\
Lm9yZ4IQKi53aWt0aW9uYXJ5Lm9yZ4IRKi5tLm1lZGlhd2lraS5vcmeCESoubS53\
aWtpcGVkaWEub3JnghEqLm0ud2lraWJvb2tzLm9yZ4IQKi5tLndpa2lkYXRhLm9y\
Z4IRKi5tLndpa2ltZWRpYS5vcmeCGyoubS53aWtpbWVkaWFmb3VuZGF0aW9uLm9y\
Z4IQKi5tLndpa2luZXdzLm9yZ4IRKi5tLndpa2lxdW90ZS5vcmeCEioubS53aWtp\
c291cmNlLm9yZ4ITKi5tLndpa2l2ZXJzaXR5Lm9yZ4ISKi5tLndpa2l2b3lhZ2Uu\
b3JnghIqLm0ud2lrdGlvbmFyeS5vcmeCFCouemVyby53aWtpcGVkaWEub3Jngg1t\
ZWRpYXdpa2kub3Jngg13aWtpYm9va3Mub3Jnggx3aWtpZGF0YS5vcmeCDXdpa2lt\
ZWRpYS5vcmeCF3dpa2ltZWRpYWZvdW5kYXRpb24ub3Jnggx3aWtpbmV3cy5vcmeC\
DXdpa2lxdW90ZS5vcmeCDndpa2lzb3VyY2Uub3Jngg93aWtpdmVyc2l0eS5vcmeC\
Dndpa2l2b3lhZ2Uub3Jngg53aWt0aW9uYXJ5Lm9yZ4INd2lraXBlZGlhLm9yZzAJ\
BgNVHRMEAjAAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjBJBgNVHR8E\
QjBAMD6gPKA6hjhodHRwOi8vY3JsLmdsb2JhbHNpZ24uY29tL2dzL2dzb3JnYW5p\
emF0aW9udmFsc2hhMmcyLmNybDCBoAYIKwYBBQUHAQEEgZMwgZAwTQYIKwYBBQUH\
MAKGQWh0dHA6Ly9zZWN1cmUuZ2xvYmFsc2lnbi5jb20vY2FjZXJ0L2dzb3JnYW5p\
emF0aW9udmFsc2hhMmcycjEuY3J0MD8GCCsGAQUFBzABhjNodHRwOi8vb2NzcDIu\
Z2xvYmFsc2lnbi5jb20vZ3Nvcmdhbml6YXRpb252YWxzaGEyZzIwHQYDVR0OBBYE\
FPijzqMJdm7bqDx4SGOcGUzAx0qdMB8GA1UdIwQYMBaAFJbeYfG9HBYpUxzAzH07\
gwBA5hp8MA0GCSqGSIb3DQEBCwUAA4IBAQC45+nGVISGOZctc9mxhil3EDmlBIzY\
5mQJ+APT5oUGthZfe6v9lP7yRLIEhHMDl72Jrnzzx3ksUnAqJTOcsnuzQvZq45pn\
gOk/sO6ilkOun/u5QBigxne1/P4g2SYkISqRqA0Z9FloEd6odDb6dbIHhhz270rH\
3pjewMLq6OA09eklPav4f3NiBL/VcqG53TRTJW6eHxZuEsGAgBmwk6jKf8e+BjmZ\
4V9POUs5kH7d1OJs9d5Fv9y3t/Yt1pGaHyK/DTUbYVhMyn0EaLxd3FLJ9ABKpQJ+\
OUcTfe55U2Ox1H/87b6Ca04DDl3u2i87jPbhgshWSNwU8+llHCst0sbG"};

    Certs::ocsp_response_t resp = check_ocsp_chain_ (chain);
    LogDebug("Certs_::check_ocsp_chain_ response : " << (int) resp);
    BOOST_REQUIRE(resp == Certs::ocsp_response_t::OCSP_CERT_ERROR);
}

BOOST_AUTO_TEST_CASE(Certs_OCSP_negative_2) {
    // Last Certificate is corrupted

    chain_t chain = {
            "MIIH1jCCBr6gAwIBAgISESGXLjKl5bLinUct/tty1iduMA0GCSqGSIb3DQEBCwUA\
MGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYD\
VQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hB\
MjU2IC0gRzIwHhcNMTQxMjE2MjEyNDAzWhcNMTcwMjE5MTIwMDAwWjB5MQswCQYD\
VQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNU2FuIEZyYW5j\
aXNjbzEjMCEGA1UEChMaV2lraW1lZGlhIEZvdW5kYXRpb24sIEluYy4xGDAWBgNV\
BAMMDyoud2lraXBlZGlhLm9yZzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\
ggEBAMH1s5FRkOrf7p3fQNqqKbre0J/7w3isYDt/tRZw4bHm7mI73Y5335iwulvr\
Bmsq93RSMHizLx8J0RdkKcfitWS/o0kIKP1wehDzHOerH6s1e7Z3j/uI6mMzDZMs\
EWDnPA21kwqtXEIwYEAj+tRU832j3CeJ3pMCE75uE+lnN0hVJIXd2c0/hnPRAWTV\
ENV6FQGCy1zwowlndvFTALQ+4LSCNtZnwVtSecgKVPAO/WkLMk2OdLB6UITT1wPN\
iP2qzm2uFWetO/MzN6paOiS2DqXFp4r7KZTSNOl3CTn8MufKGPqA0ajJJDLSX0/K\
DmC1Sw6ndBerUuRDSaDeEq2I8HMCAwEAAaOCBGkwggRlMA4GA1UdDwEB/wQEAwIF\
oDBJBgNVHSAEQjBAMD4GBmeBDAECAjA0MDIGCCsGAQUFBwIBFiZodHRwczovL3d3\
dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzCCAq4GA1UdEQSCAqUwggKhgg8q\
Lndpa2lwZWRpYS5vcmeCDyoubWVkaWF3aWtpLm9yZ4IPKi53aWtpYm9va3Mub3Jn\
gg4qLndpa2lkYXRhLm9yZ4IPKi53aWtpbWVkaWEub3JnghkqLndpa2ltZWRpYWZv\
dW5kYXRpb24ub3Jngg4qLndpa2luZXdzLm9yZ4IPKi53aWtpcXVvdGUub3JnghAq\
Lndpa2lzb3VyY2Uub3JnghEqLndpa2l2ZXJzaXR5Lm9yZ4IQKi53aWtpdm95YWdl\
Lm9yZ4IQKi53aWt0aW9uYXJ5Lm9yZ4IRKi5tLm1lZGlhd2lraS5vcmeCESoubS53\
aWtpcGVkaWEub3JnghEqLm0ud2lraWJvb2tzLm9yZ4IQKi5tLndpa2lkYXRhLm9y\
Z4IRKi5tLndpa2ltZWRpYS5vcmeCGyoubS53aWtpbWVkaWFmb3VuZGF0aW9uLm9y\
Z4IQKi5tLndpa2luZXdzLm9yZ4IRKi5tLndpa2lxdW90ZS5vcmeCEioubS53aWtp\
c291cmNlLm9yZ4ITKi5tLndpa2l2ZXJzaXR5Lm9yZ4ISKi5tLndpa2l2b3lhZ2Uu\
b3JnghIqLm0ud2lrdGlvbmFyeS5vcmeCFCouemVyby53aWtpcGVkaWEub3Jngg1t\
ZWRpYXdpa2kub3Jngg13aWtpYm9va3Mub3Jnggx3aWtpZGF0YS5vcmeCDXdpa2lt\
ZWRpYS5vcmeCF3dpa2ltZWRpYWZvdW5kYXRpb24ub3Jnggx3aWtpbmV3cy5vcmeC\
DXdpa2lxdW90ZS5vcmeCDndpa2lzb3VyY2Uub3Jngg93aWtpdmVyc2l0eS5vcmeC\
Dndpa2l2b3lhZ2Uub3Jngg53aWt0aW9uYXJ5Lm9yZ4INd2lraXBlZGlhLm9yZzAJ\
BgNVHRMEAjAAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjBJBgNVHR8E\
QjBAMD6gPKA6hjhodHRwOi8vY3JsLmdsb2JhbHNpZ24uY29tL2dzL2dzb3JnYW5p\
emF0aW9udmFsc2hhMmcyLmNybDCBoAYIKwYBBQUHAQEEgZMwgZAwTQYIKwYBBQUH\
MAKGQWh0dHA6Ly9zZWN1cmUuZ2xvYmFsc2lnbi5jb20vY2FjZXJ0L2dzb3JnYW5p\
emF0aW9udmFsc2hhMmcycjEuY3J0MD8GCCsGAQUFBzABhjNodHRwOi8vb2NzcDIu\
Z2xvYmFsc2lnbi5jb20vZ3Nvcmdhbml6YXRpb252YWxzaGEyZzIwHQYDVR0OBBYE\
FPijzqMJdm7bqDx4SGOcGUzAx0qdMB8GA1UdIwQYMBaAFJbeYfG9HBYpUxzAzH07\
gwBA5hp8MA0GCSqGSIb3DQEBCwUAA4IBAQC45+nGVISGOZctc9mxhil3EDmlBIzY\
5mQJ+APT5oUGthZfe6v9lP7yRLIEhHMDl72Jrnzzx3ksUnAqJTOcsnuzQvZq45pn\
gOk/sO6ilkOun/u5QBigxne1/P4g2SYkISqRqA0Z9FloEd6odDb6dbIHhhz270rH\
3pjewMLq6OA09eklPav4f3NiBL/VcqG53TRTJW6eHxZuEsGAgBmwk6jKf8e+BjmZ\
4V9POUs5kH7d1OJs9d5Fv9y3t/Yt1pGaHyK/DTUbYVhMyn0EaLxd3FLJ9ABKpQJ+\
OUcTfe55U2Ox1H/87b6Ca04DDl3u2i87jPbhgshWSNwU8+llHCst0sbG",

"MIIEaTCCA1GgAwIBAgILBAAAAAABRE7wQkcwDQYJKoZIhvcNAQELBQAwVzELMAkG\
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw0xNDAyMjAxMDAw\
MDBaFw0yNDAyMjAxMDAwMDBaMGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\
YWxTaWduIG52LXNhMTwwOgYDVQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBW\
YWxpZGF0aW9uIENBIC0gU0hBMjU2IC0gRzIwggEiMA0GCSqGSIb3DQEBAQUAA4IB\
DwAwggEKAoIBAQDHDmw/I5N/zHClnSDDDlM/fsBOwphJykfVI+8DNIV0yKMCLkZc\
C33JiJ1Pi/D4nGyMVTXbv/Kz6vvjVudKRtkTIso21ZvBqOOWQ5PyDLzm+ebomchj\
SHh/VzZpGhkdWtHUfcKc1H/hgBKueuqI6lfYygoKOhJJomIZeg0k9zfrtHOSewUj\
mxK1zusp36QUArkBpdSmnENkiN74fv7j9R7l/tyjqORmMdlMJekYuYlZCa7pnRxt\
Nw9KHjUgKOKv1CGLAcRFrW4rY6uSa2EKTSDtc7p8zv4WtdufgPDWi2zZCHlKT3hl\
2pK8vjX5s8T5J4BO/5ZS5gIg4Qdz6V0rvbLxAgMBAAGjggElMIIBITAOBgNVHQ8B\
Af8EBAMCAQYwEgYDVR0TAQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQUlt5h8b0cFilT\
HMDMfTuDAEDmGnwwRwYDVR0gBEAwPjA8BgRVHSAAMDQwMgYIKwYBBQUHAgEWJmh0\
dHBzOi8vd3d3Lmdsb2JhbHNpZ24uY29tL3JlcG9zaXRvcnkvMDMGA1UdHwQsMCow\
KKAmoCSGImh0dHA6Ly9jcmwuZ2xvYmFsc2lnbi5uZXQvcm9vdC5jcmwwPQYIKwYB\
BQUHAQEEMTAvMC0GCCsGAQUFBzABhiFodHRwOi8vb2NzcC5nbG9iYWxzaWduLmNv\
bS9yb290cjEwHwYDVR0jBBgwFoAUYHtmGkUNl8qJUC99BM00qP/8/UswDQYJKoZI\
hvcNAQELBQADggEBAEYq7l69rgFgNzERhnF0tkZJyBAW/i9iIxerH4f4gu3K3w4s\
32R1juUYcqeMOovJrKV3UPfvnqTgoI8UV6MqX+x+bRDmuo2wCId2Dkyy2VG7EQLy\
XN0cvfNVlg/UBsD84iOKJHDTu/B5GqdhcIOKrwbFINihY9Bsrk8y1658GEV1BSl3\
30JAZGSGvip2CTFvHST0mdCF/vIhCPnG9vHQWe3WVjwIKANnuvD58ZAWR65n5ryA\
SOlCdjSXVWkkDoPWoC209fN5ikkodBpBocLTJIg1MGCUF7ThBCIxPTsvFwayuJ2G\
K1pp74P1S8SqtCr4fKGxhZSM9AyHDPSsQPhZSZg=",

"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\
MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\
YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\
aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\
jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\
xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\
1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\
snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\
U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\
9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\
BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\
AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\
yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\
38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\
AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\
DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\
HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4"};

    Certs::ocsp_response_t resp = check_ocsp_chain_ (chain);
    LogDebug("Certs_::check_ocsp_chain_ response : " << (int) resp);
    BOOST_REQUIRE(resp == Certs::ocsp_response_t::OCSP_CERT_ERROR);
}

BOOST_AUTO_TEST_CASE(Certs_OCSP_positive_1) {

    chain_t chain = {
    // MBANK, signed by SYMANTEC, expires 04 Feb 2016
    "MIIGXDCCBUSgAwIBAgIQKJK70TuBw91HAA0BqZSPETANBgkqhkiG9w0BAQsFADB3\
MQswCQYDVQQGEwJVUzEdMBsGA1UEChMUU3ltYW50ZWMgQ29ycG9yYXRpb24xHzAd\
BgNVBAsTFlN5bWFudGVjIFRydXN0IE5ldHdvcmsxKDAmBgNVBAMTH1N5bWFudGVj\
IENsYXNzIDMgRVYgU1NMIENBIC0gRzMwHhcNMTUwMTE1MDAwMDAwWhcNMTYwMjA0\
MjM1OTU5WjCB5zETMBEGCysGAQQBgjc8AgEDEwJQTDEdMBsGA1UEDxMUUHJpdmF0\
ZSBPcmdhbml6YXRpb24xEzARBgNVBAUTCjAwMDAwMjUyMzcxCzAJBgNVBAYTAlBM\
MQ8wDQYDVQQRDAYwMC05NTAxFDASBgNVBAgMC21hem93aWVja2llMREwDwYDVQQH\
DAhXYXJzemF3YTEWMBQGA1UECQwNU2VuYXRvcnNrYSAxODETMBEGA1UECgwKbUJh\
bmsgUy5BLjEOMAwGA1UECwwFbUJhbmsxGDAWBgNVBAMMD29ubGluZS5tYmFuay5w\
bDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALsoKHBnIkP1AoHBKPYm\
JkCOgvwFeKgrLGDjpte9eVljMGYPkpWv2GtwV2lKAy47fCOOtBGfVR7qp3C3kR06\
Eep7tKm0C9/X75wTIAu2ulfdooX89JZ2UfMyBs8q0eyGPbBz42g5FQx3cey+OUjU\
aadDwfxfn9UKFABrq/wowkYLIpFejQePmztdNepinOVcbZ4NVrsMCkxHnyYXR+Kh\
Tn/UEpX8FEBx9Ra96AbeXY7f6IpPf8IwoAF3lp00R0nigCfuhWF/GrX0+GX8f/vV\
dtnNozuBN59tWPmpcTUmpSbDJFMCJbEYwX+cKo8Kq38qOp/c2y7x/Cphuv0hapGp\
Q78CAwEAAaOCAnEwggJtMBoGA1UdEQQTMBGCD29ubGluZS5tYmFuay5wbDAJBgNV\
HRMEAjAAMA4GA1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYB\
BQUHAwIwZgYDVR0gBF8wXTBbBgtghkgBhvhFAQcXBjBMMCMGCCsGAQUFBwIBFhdo\
dHRwczovL2Quc3ltY2IuY29tL2NwczAlBggrBgEFBQcCAjAZGhdodHRwczovL2Qu\
c3ltY2IuY29tL3JwYTAfBgNVHSMEGDAWgBQBWavn3ToLWaZkY9bPIAdX1ZHnajAr\
BgNVHR8EJDAiMCCgHqAchhpodHRwOi8vc3Iuc3ltY2IuY29tL3NyLmNybDBXBggr\
BgEFBQcBAQRLMEkwHwYIKwYBBQUHMAGGE2h0dHA6Ly9zci5zeW1jZC5jb20wJgYI\
KwYBBQUHMAKGGmh0dHA6Ly9zci5zeW1jYi5jb20vc3IuY3J0MIIBBAYKKwYBBAHW\
eQIEAgSB9QSB8gDwAHYApLkJkLQYWBSHuxOizGdwCjw1mAT5G9+443fNDsgN3BAA\
AAFK7fScbAAABAMARzBFAiEAuFUfNYF/LMBuKewPE8xTrmye39LyNfBh5roPCaVq\
ReQCIEOB7ktB3xu7yd/pHuXSWdXzZpOmVQiMChsoE46TIBryAHYAVhQGmi/XwuzT\
9eG9RLI+x0Z2ubyZEVzA75SYVdaJ0N0AAAFK7fSemAAABAMARzBFAiAaixUME3mn\
rmzLb8WpwEfV60cXQ1945LWlLxCL5VVR6wIhAMBCNzFiOMtnLu0oBWHo1RrJxMnf\
LbWvlnrdF7yloeAjMA0GCSqGSIb3DQEBCwUAA4IBAQCIvFY/1sEmBKEMlwpJCvHD\
U0yx67QDsiJ0Fo4MZmgOUZ1AH/gSKUUy7j6RnQ/e9v5DlKKlWZpUpr5KqaXcOOWq\
vSeuWoKVCnjdsVyYJm1zW7Py3Khrkbef53gZjSR+X5gGlRC/WeeDwUxoCm/nJ4S0\
SReh+urkTFGUdSPCsD4mQk3zI1wNhE7Amb2mUTIaSLzabnN89hn9jlvQwLH2Wkf2\
aFmUlsB1C6YFMqVPRfHuxyPUb2zjw+ll7UStQxuSSTpwBmW1g/dIhtle9+o8i3z2\
WJAT38TP3mPw8SUWLbgGyih6bsB6eBxFEM5awP60XXjZfVAmoVLlj9oWYNQrZLwk",

    // SYMANTEC, signed by VERISIGN, expires 30 Oct 2023
    "MIIFKzCCBBOgAwIBAgIQfuFKb2/v8tN/P61lTTratDANBgkqhkiG9w0BAQsFADCB\
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\
aG9yaXR5IC0gRzUwHhcNMTMxMDMxMDAwMDAwWhcNMjMxMDMwMjM1OTU5WjB3MQsw\
CQYDVQQGEwJVUzEdMBsGA1UEChMUU3ltYW50ZWMgQ29ycG9yYXRpb24xHzAdBgNV\
BAsTFlN5bWFudGVjIFRydXN0IE5ldHdvcmsxKDAmBgNVBAMTH1N5bWFudGVjIENs\
YXNzIDMgRVYgU1NMIENBIC0gRzMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\
AoIBAQDYoWV0I+grZOIy1zM3PY71NBZI3U9/hxz4RCMTjvsR2ERaGHGOYBYmkpv9\
FwvhcXBC/r/6HMCqo6e1cej/GIP23xAKE2LIPZyn3i4/DNkd5y77Ks7Imn+Hv9hM\
BBUyydHMlXGgTihPhNk1++OGb5RT5nKKY2cuvmn2926OnGAE6yn6xEdC0niY4+wL\
pZLct5q9gGQrOHw4CVtm9i2VeoayNC6FnpAOX7ddpFFyRnATv2fytqdNFB5suVPu\
IxpOjUhVQ0GxiXVqQCjFfd3SbtICGS97JJRL6/EaqZvjI5rq+jOrCiy39GAI3Z8c\
zd0tAWaAr7MvKR0juIrhoXAHDDQPAgMBAAGjggFdMIIBWTAvBggrBgEFBQcBAQQj\
MCEwHwYIKwYBBQUHMAGGE2h0dHA6Ly9zMi5zeW1jYi5jb20wEgYDVR0TAQH/BAgw\
BgEB/wIBADBlBgNVHSAEXjBcMFoGBFUdIAAwUjAmBggrBgEFBQcCARYaaHR0cDov\
L3d3dy5zeW1hdXRoLmNvbS9jcHMwKAYIKwYBBQUHAgIwHBoaaHR0cDovL3d3dy5z\
eW1hdXRoLmNvbS9ycGEwMAYDVR0fBCkwJzAloCOgIYYfaHR0cDovL3MxLnN5bWNi\
LmNvbS9wY2EzLWc1LmNybDAOBgNVHQ8BAf8EBAMCAQYwKQYDVR0RBCIwIKQeMBwx\
GjAYBgNVBAMTEVN5bWFudGVjUEtJLTEtNTMzMB0GA1UdDgQWBBQBWavn3ToLWaZk\
Y9bPIAdX1ZHnajAfBgNVHSMEGDAWgBR/02Wnwt3su/AwCfNDOfoCrzMxMzANBgkq\
hkiG9w0BAQsFAAOCAQEAQgFVe9AWGl1Y6LubqE3X89frE5SG1n8hC0e8V5uSXU8F\
nzikEHzPg74GQ0aNCLxq1xCm+quvL2GoY/Jl339MiBKIT7Np2f8nwAqXkY9W+4nE\
qLuSLRtzsMarNvSWbCAI7woeZiRFT2cAQMgHVHQzO6atuyOfZu2iRHA0+w7qAf3P\
eHTfp61Vt19N9tY/4IbOJMdCqRMURDVLtt/JYKwMf9mTIUvunORJApjTYHtcvNUw\
LwfORELEC5n+5p/8sHiGUW3RLJ3GlvuFgrsEL/digO9i2n/2DqyQuFa9eT/ygG6j\
2bkPXToHHZGThkspTOHcteHgM52zyzaRS/6htO7w+Q=="
    };

    Certs::ocsp_response_t resp = check_ocsp_chain_ (chain);
    LogDebug("Certs_::check_ocsp_chain_ response : " << (int) resp);
    BOOST_REQUIRE(resp == Certs::ocsp_response_t::OCSP_APP_OK);
}

BOOST_AUTO_TEST_CASE(find_app_signatures_1) {

    // App1
    app_t app1("app_id", "pkg_id", 101, {});
    ocsp_urls_t ocsp_urls;
    std::string path1 = std::string(TEST_APP_SIGNATURES_DIR) + std::string("/app1");

    find_app_signatures (app1, path1, ocsp_urls);
    BOOST_REQUIRE(app1.signatures.size() == 2);
    // set signatures/certificates in defined oder;
    sort(app1);

    app_t origin1("app_id", "pkg_id", 101, {});
    chain_t chain1 = {"MIIClDCCAf2gAwIBAgIGAT4hYbcpMA0GCSqGSIb3DQEBBQUAMIGEMQswCQYDVQQGEwJLUjEOMAwG\
A1UECAwFU3V3b24xDjAMBgNVBAcMBVN1d29uMRYwFAYDVQQKDA1UaXplbiBUZXN0IENBMSAwHgYD\
VQQLDBdUaXplbiBEZXZlbG9wZXIgVGVzdCBDQTEbMBkGA1UEAwwSVGl6ZW4gRGV2ZWxvcGVyIENB\
MB4XDTEzMDQxOTA4MjA1MloXDTQwMDkwNDA4MjA1MVowgZUxCzAJBgNVBAYTAlBMMREwDwYDVQQI\
DAhNYXpvdmlhbjEPMA0GA1UEBwwGV2Fyc2F3MQ4wDAYDVQQKDAVTUlBPTDERMA8GA1UECwwIS1NG\
L1dTU1AxJTAjBgkqhkiG9w0BCQEWFmoua296ZXJza2lAc2Ftc3VuZy5jb20xGDAWBgNVBAMMD0ph\
bnVzeiBLb3plcnNraTCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAs0REWSsOn/QyVDSjSTRE\
0W+LacX4cifRYI16nQi8WJhCAymhOg4UVXUk31Iwta8lOnQvgoce8bR+/dbCzDBmnogq8KXWlEtn\
Ma3X6Tvz5BZfNy4Zj44G/aK0tJvnBj28h2ZZe545BNNW4zKR4SvNie9uM8v1r16PZaaS0YxOXl0C\
AwEAATANBgkqhkiG9w0BAQUFAAOBgQCGuwLCcQAAQz2Op83gTl0Pb+f7AinL8d3XGRC8dtFPqSrZ\
wN3gEEIQxQeYLahEVPAsD1K9aWebbWm/sjpDERKW7hmYvGYz90Z+ocLKdork5XgQWqVGt7qi+pxZ\
x6VDuNVxDrQtsX/hLf/YBhZJuzs/LSdlErUKQM8fdxvVzbld3w==",
            "MIICpzCCAhCgAwIBAgIJAKzDjmEF+1OXMA0GCSqGSIb3DQEBBQUAMIGTMQswCQYDVQQGEwJLUjEO\
MAwGA1UECAwFU3V3b24xDjAMBgNVBAcMBVN1d29uMRYwFAYDVQQKDA1UaXplbiBUZXN0IENBMSUw\
IwYDVQQLDBxUaXplbiBUZXN0IERldmVsb3BlciBSb290IENBMSUwIwYDVQQDDBxUaXplbiBUZXN0\
IERldmVsb3BlciBSb290IENBMB4XDTEyMTAyOTEzMDEyMloXDTIyMTAyNzEzMDEyMlowgYQxCzAJ\
BgNVBAYTAktSMQ4wDAYDVQQIDAVTdXdvbjEOMAwGA1UEBwwFU3V3b24xFjAUBgNVBAoMDVRpemVu\
IFRlc3QgQ0ExIDAeBgNVBAsMF1RpemVuIERldmVsb3BlciBUZXN0IENBMRswGQYDVQQDDBJUaXpl\
biBEZXZlbG9wZXIgQ0EwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAMyG0DSTHBgalQo1seDK\
xpCU61gji+QQlxQkPQOvBrmuF6Z90zFCprTtg2sRjTLCNoRd75+VCCHuKGcrD27t7hwAekusPrpz\
dsq5QoBMvNjGDM22lC45PJ4d86DEDY4erxeJ5aSQxqbfXK4pKe9NwxdkKuA8dTYZM1UcmhXs7YAL\
AgMBAAGjEDAOMAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEFBQADgYEACbr/OPNMJ+Ejrxfm/YjC\
iRPpjJLnwXS2IDtitbxot6bEdZkZvOFXOC0Ca4GT+jtvOcSlU7tM3Mdd1MrKe1kkoVd1vhCV8V4C\
K3/DPj8aN3rxfMfQitA6XMDcxzhsyMWz56OdifX50dvS/G/ad+kGhNhOOEKSE8zUyEDCGwqkfXk="};

    chain_t chain2 = {"MIICmzCCAgQCCQDXI7WLdVZwiTANBgkqhkiG9w0BAQUFADCBjzELMAkGA1UEBhMCS1IxDjAMBgNV\
BAgMBVN1d29uMQ4wDAYDVQQHDAVTdXdvbjEWMBQGA1UECgwNVGl6ZW4gVGVzdCBDQTEiMCAGA1UE\
CwwZVGl6ZW4gRGlzdHJpYnV0b3IgVGVzdCBDQTEkMCIGA1UEAwwbVGl6ZW4gUHVibGljIERpc3Ry\
aWJ1dG9yIENBMB4XDTEyMTAyOTEzMDMwNFoXDTIyMTAyNzEzMDMwNFowgZMxCzAJBgNVBAYTAktS\
MQ4wDAYDVQQIDAVTdXdvbjEOMAwGA1UEBwwFU3V3b24xFjAUBgNVBAoMDVRpemVuIFRlc3QgQ0Ex\
IjAgBgNVBAsMGVRpemVuIERpc3RyaWJ1dG9yIFRlc3QgQ0ExKDAmBgNVBAMMH1RpemVuIFB1Ymxp\
YyBEaXN0cmlidXRvciBTaWduZXIwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBALtMvlc5hENK\
90ZdA+y66+Sy0enD1gpZDBh5T9RP0oRsptJv5jjNTseQbQi0SZOdOXb6J7iQdlBCtR343RpIEz8H\
mrBy7mSY7mgwoU4EPpp4CTSUeAuKcmvrNOngTp5Hv7Ngf02TTHOLK3hZLpGayaDviyNZB5PdqQdB\
hokKjzAzAgMBAAEwDQYJKoZIhvcNAQEFBQADgYEAvGp1gxxAIlFfhJH1efjb9BJK/rtRkbYn9+Ez\
GEbEULg1svsgnyWisFimI3uFvgI/swzr1eKVY3Sc8MQ3+Fdy3EkbDZ2+WAubhcEkorTWjzWz2fL1\
vKaYjeIsuEX6TVRUugHWudPzcEuQRLQf8ibZWjbQdBmpeQYBMg5x+xKLCJc=",
            "MIICtDCCAh2gAwIBAgIJAMDbehElPNKvMA0GCSqGSIb3DQEBBQUAMIGVMQswCQYDVQQGEwJLUjEO\
MAwGA1UECAwFU3V3b24xDjAMBgNVBAcMBVN1d29uMRYwFAYDVQQKDA1UaXplbiBUZXN0IENBMSMw\
IQYDVQQLDBpUVGl6ZW4gRGlzdHJpYnV0b3IgVGVzdCBDQTEpMCcGA1UEAwwgVGl6ZW4gUHVibGlj\
IERpc3RyaWJ1dG9yIFJvb3QgQ0EwHhcNMTIxMDI5MTMwMjUwWhcNMjIxMDI3MTMwMjUwWjCBjzEL\
MAkGA1UEBhMCS1IxDjAMBgNVBAgMBVN1d29uMQ4wDAYDVQQHDAVTdXdvbjEWMBQGA1UECgwNVGl6\
ZW4gVGVzdCBDQTEiMCAGA1UECwwZVGl6ZW4gRGlzdHJpYnV0b3IgVGVzdCBDQTEkMCIGA1UEAwwb\
VGl6ZW4gUHVibGljIERpc3RyaWJ1dG9yIENBMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDe\
OTS/3nXvkDEmsFCJIvRlQ3RKDcxdWJJp625pFqHdmoJBdV+x6jl1raGK2Y1sp2Gdvpjc/z92yzAp\
bE/UVLPh/tRNZPeGhzU4ejDDm7kzdr2f7Ia0U98K+OoY12ucwg7TYNItj9is7Cj4blGfuMDzd2ah\
2AgnCGlwNwV/pv+uVQIDAQABoxAwDjAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBBQUAA4GBACqJ\
KO33YdoGudwanZIxMdXuxnnD9R6u72ltKk1S4zPfMJJv482CRGCI4FK6djhlsI4i0Lt1SVIJEed+\
yc3qckGm19dW+4xdlkekon7pViEBWuyHw8OWv3RXtTum1+PGHjBJ2eYY4ZKIpz73U/1NC16sTB/0\
VhfnkHwPltmrpYVe"};


    origin1.signatures.push_back(chain1);
    origin1.signatures.push_back(chain2);
    // set signatures/certificates in defined oder;
    sort(origin1);

    LogDebug("APP1: " << app1.str() << ", CERTS: " << app1.str_certs());
    LogDebug("ORIG: " << origin1.str() << ", CERTS: " << origin1.str_certs());

    BOOST_REQUIRE(app1 == origin1);

    // App_2
    app_t app2("app_id", "pkg_id", 102, {});
    std::string path2 = std::string(TEST_APP_SIGNATURES_DIR) + std::string("/app_2");

    find_app_signatures (app2, path2, ocsp_urls);
    BOOST_REQUIRE(app2.signatures.size() == 1);
    // set signatures/certificates in defined oder;
    sort(app2);


    chain_t chain3 = {"MIICmzCCAgQCCQDXI7WLdVZwiTANBgkqhkiG9w0BAQUFADCBjzELMAkGA1UEBhMCS1IxDjAMBgNV\
BAgMBVN1d29uMQ4wDAYDVQQHDAVTdXdvbjEWMBQGA1UECgwNVGl6ZW4gVGVzdCBDQTEiMCAGA1UE\
CwwZVGl6ZW4gRGlzdHJpYnV0b3IgVGVzdCBDQTEkMCIGA1UEAwwbVGl6ZW4gUHVibGljIERpc3Ry\
aWJ1dG9yIENBMB4XDTEyMTAyOTEzMDMwNFoXDTIyMTAyNzEzMDMwNFowgZMxCzAJBgNVBAYTAktS\
MQ4wDAYDVQQIDAVTdXdvbjEOMAwGA1UEBwwFU3V3b24xFjAUBgNVBAoMDVRpemVuIFRlc3QgQ0Ex\
IjAgBgNVBAsMGVRpemVuIERpc3RyaWJ1dG9yIFRlc3QgQ0ExKDAmBgNVBAMMH1RpemVuIFB1Ymxp\
YyBEaXN0cmlidXRvciBTaWduZXIwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBALtMvlc5hENK\
90ZdA+y66+Sy0enD1gpZDBh5T9RP0oRsptJv5jjNTseQbQi0SZOdOXb6J7iQdlBCtR343RpIEz8H\
mrBy7mSY7mgwoU4EPpp4CTSUeAuKcmvrNOngTp5Hv7Ngf02TTHOLK3hZLpGayaDviyNZB5PdqQdB\
hokKjzAzAgMBAAEwDQYJKoZIhvcNAQEFBQADgYEAvGp1gxxAIlFfhJH1efjb9BJK/rtRkbYn9+Ez\
GEbEULg1svsgnyWisFimI3uFvgI/swzr1eKVY3Sc8MQ3+Fdy3EkbDZ2+WAubhcEkorTWjzWz2fL1\
vKaYjeIsuEX6TVRUugHWudPzcEuQRLQf8ibZWjbQdBmpeQYBMg5x+xKLCJc=",
                "MIICtDCCAh2gAwIBAgIJAMDbehElPNKvMA0GCSqGSIb3DQEBBQUAMIGVMQswCQYDVQQGEwJLUjEO\
MAwGA1UECAwFU3V3b24xDjAMBgNVBAcMBVN1d29uMRYwFAYDVQQKDA1UaXplbiBUZXN0IENBMSMw\
IQYDVQQLDBpUVGl6ZW4gRGlzdHJpYnV0b3IgVGVzdCBDQTEpMCcGA1UEAwwgVGl6ZW4gUHVibGlj\
IERpc3RyaWJ1dG9yIFJvb3QgQ0EwHhcNMTIxMDI5MTMwMjUwWhcNMjIxMDI3MTMwMjUwWjCBjzEL\
MAkGA1UEBhMCS1IxDjAMBgNVBAgMBVN1d29uMQ4wDAYDVQQHDAVTdXdvbjEWMBQGA1UECgwNVGl6\
ZW4gVGVzdCBDQTEiMCAGA1UECwwZVGl6ZW4gRGlzdHJpYnV0b3IgVGVzdCBDQTEkMCIGA1UEAwwb\
VGl6ZW4gUHVibGljIERpc3RyaWJ1dG9yIENBMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDe\
OTS/3nXvkDEmsFCJIvRlQ3RKDcxdWJJp625pFqHdmoJBdV+x6jl1raGK2Y1sp2Gdvpjc/z92yzAp\
bE/UVLPh/tRNZPeGhzU4ejDDm7kzdr2f7Ia0U98K+OoY12ucwg7TYNItj9is7Cj4blGfuMDzd2ah\
2AgnCGlwNwV/pv+uVQIDAQABoxAwDjAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBBQUAA4GBACqJ\
KO33YdoGudwanZIxMdXuxnnD9R6u72ltKk1S4zPfMJJv482CRGCI4FK6djhlsI4i0Lt1SVIJEed+\
yc3qckGm19dW+4xdlkekon7pViEBWuyHw8OWv3RXtTum1+PGHjBJ2eYY4ZKIpz73U/1NC16sTB/0\
VhfnkHwPltmrpYVe"};

    app_t origin2("app_id", "pkg_id", 102, {});
    origin2.signatures.push_back(chain3);

    // set signatures/certificates in defined oder;
    sort(origin2);

    BOOST_REQUIRE(app2 == origin2);
}

BOOST_AUTO_TEST_CASE(find_app_signatures_negative) {

    // App1
    app_t app1("app_id", "pkg_id", 101, {});
    ocsp_urls_t ocsp_urls;
    std::string path1 = std::string(TEST_APP_SIGNATURES_DIR) + std::string("/app3");

    find_app_signatures (app1, path1, ocsp_urls);
    // signature exists, but contains error - should not be parsed
    BOOST_REQUIRE(app1.signatures.empty());
}

BOOST_AUTO_TEST_CASE(find_app_signatures_mixed) {

    app_t app("app_id", "pkg_id", 101, {});
    ocsp_urls_t ocsp_urls;
    std::string path = std::string(TEST_APP_SIGNATURES_DIR) + std::string("/app4");

    find_app_signatures (app, path, ocsp_urls);
    // 2 signatures exist, but one of them contains error - only one should be parsed
    BOOST_REQUIRE(app.signatures.size() == 1);

    app_t origin("app_id", "pkg_id", 101, {});
    chain_t chain = {"MIIClDCCAf2gAwIBAgIGAT4hYbcpMA0GCSqGSIb3DQEBBQUAMIGEMQswCQYDVQQGEwJLUjEOMAwG\
A1UECAwFU3V3b24xDjAMBgNVBAcMBVN1d29uMRYwFAYDVQQKDA1UaXplbiBUZXN0IENBMSAwHgYD\
VQQLDBdUaXplbiBEZXZlbG9wZXIgVGVzdCBDQTEbMBkGA1UEAwwSVGl6ZW4gRGV2ZWxvcGVyIENB\
MB4XDTEzMDQxOTA4MjA1MloXDTQwMDkwNDA4MjA1MVowgZUxCzAJBgNVBAYTAlBMMREwDwYDVQQI\
DAhNYXpvdmlhbjEPMA0GA1UEBwwGV2Fyc2F3MQ4wDAYDVQQKDAVTUlBPTDERMA8GA1UECwwIS1NG\
L1dTU1AxJTAjBgkqhkiG9w0BCQEWFmoua296ZXJza2lAc2Ftc3VuZy5jb20xGDAWBgNVBAMMD0ph\
bnVzeiBLb3plcnNraTCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAs0REWSsOn/QyVDSjSTRE\
0W+LacX4cifRYI16nQi8WJhCAymhOg4UVXUk31Iwta8lOnQvgoce8bR+/dbCzDBmnogq8KXWlEtn\
Ma3X6Tvz5BZfNy4Zj44G/aK0tJvnBj28h2ZZe545BNNW4zKR4SvNie9uM8v1r16PZaaS0YxOXl0C\
AwEAATANBgkqhkiG9w0BAQUFAAOBgQCGuwLCcQAAQz2Op83gTl0Pb+f7AinL8d3XGRC8dtFPqSrZ\
wN3gEEIQxQeYLahEVPAsD1K9aWebbWm/sjpDERKW7hmYvGYz90Z+ocLKdork5XgQWqVGt7qi+pxZ\
x6VDuNVxDrQtsX/hLf/YBhZJuzs/LSdlErUKQM8fdxvVzbld3w=="};
    origin.signatures.push_back(chain);

    BOOST_REQUIRE(app == origin);
}

BOOST_AUTO_TEST_SUITE_END()
