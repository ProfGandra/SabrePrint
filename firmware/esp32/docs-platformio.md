# Compilação com PlatformIO

1. Instale VS Code e a extensão PlatformIO IDE.
2. Abra **a pasta `firmware/esp32`**, e não a raiz do repositório, como projeto PlatformIO.
3. Conecte uma placa ESP32-S3 compatível com o perfil provisório `esp32-s3-devkitc-1`.
4. Execute **Build**. Depois, selecione a porta correta e execute **Upload**.
5. Abra o monitor serial a 115200 baud para visualizar os logs.

O perfil de placa é **provisório**. Antes do upload, confirme o modelo físico, o modo de gravação e a disponibilidade das portas USB. A porta de programação pode ser diferente da porta usada como USB Host.

Este firmware **não controla impressoras**. É apenas um teste de inicialização e diagnóstico.

A implementação de USB Host deverá considerar a alimentação de VBUS e os chipsets USB-seriais das impressoras; a compatibilidade ainda não está validada.
