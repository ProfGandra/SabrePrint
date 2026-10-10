# Sabre 3D — Arquitetura de rede (decisão aprovada)

## Modo de operação inicial

O ESP32-S3 operará como **ponto de acesso Wi-Fi (SoftAP)** independente. Não é necessário roteador, conexão à internet, display ou DNS local.

| Parâmetro | Definição |
|---|---|
| Modo | Wi-Fi SoftAP |
| SSID | `Sabre3D` |
| Endereço do servidor | `http://192.168.4.1` |
| IP do ESP32 | `192.168.4.1` |
| DHCP | Habilitado para clientes |
| Segurança | WPA2-Personal, senha configurável |
| Internet | Não necessária |

**Segurança:** não gravar senha de produção no repositório. Usar senha inicial exclusiva por dispositivo ou configuração local segura; não disponibilizar AP aberto.

## Fluxo de utilização

1. Alimentar o Sabre 3D por fonte externa 5 V.
2. Conectar o celular ou computador à rede Wi-Fi `Sabre3D`.
3. Abrir `http://192.168.4.1` no navegador.
4. Enviar um arquivo G-code pela interface.
5. O ESP32 grava o arquivo no microSD e, após validação e comando do usuário, o transmite à impressora por USB serial.
6. Após o upload, o dispositivo cliente pode desconectar-se; a impressão é controlada pelo ESP32.

## Observações

- O celular poderá indicar que a rede não tem internet; isso é esperado.
- O acesso será via HTTP na rede local própria. Não expor o AP diretamente à internet.
- A impressão real dependerá da implementação e validação do USB Host, do controle de fluxo Marlin e das proteções de segurança.
- mDNS, integração com roteador e display ficam fora do escopo inicial e poderão ser considerados no futuro.
- O case será projetado **após a conclusão e validação da eletrônica**.

**Status:** decisão de arquitetura aprovada; implementação do SoftAP ainda pendente.

Desenvolvido por DGandra - 2026.
