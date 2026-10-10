# SabrePrint — Sabre 3D

> **PROJETO EM DESENVOLVIMENTO — versão experimental**
>
> O Sabre 3D ainda está em fase de prototipagem e testes. A interface disponível é demonstrativa e **não deve ser utilizada para controlar impressoras reais** nesta etapa. Funcionalidades, compatibilidade e arquitetura poderão mudar durante o desenvolvimento.

## Sobre o projeto

O **Sabre 3D** é um projeto de controlador de impressão 3D baseado em **ESP32-S3**, inspirado nas funcionalidades do Pronterface. Seu objetivo é permitir o gerenciamento de impressoras 3D com firmware Marlin por uma interface web, sem depender de um computador permanentemente conectado à impressora.

A proposta é enviar arquivos **G-code pelo navegador**, armazená-los no cartão microSD do módulo ESP32 e transmiti-los à impressora pela comunicação USB serial. **Não será necessário armazenar os arquivos na própria impressora.**

## Funcionalidades previstas

- Interface web responsiva para computadores, tablets e celulares.
- Upload e gerenciamento de arquivos G-code.
- Armazenamento dos arquivos em microSD conectado ao ESP32.
- Impressão por transmissão serial USB com controle de fluxo.
- Monitoramento de temperaturas e estado da impressão.
- Movimentação manual dos eixos e terminal G-code.
- Controles de início, pausa e cancelamento de impressão.
- Operação em rede Wi-Fi local, sem necessidade de internet.

## Hardware previsto

- ESP32-S3, preferencialmente com PSRAM.
- Cartão microSD para os arquivos.
- Porta USB Host com suporte aos dispositivos USB-seriais das controladoras.
- Fonte externa de 5 V para o módulo ESP32.

## Compatibilidade pretendida

A compatibilidade inicial será estudada com **RAMPS + Arduino Mega**, **Creality Ender 3**, **Creality Ender 5 Plus** e **JG Aurora A5S**, dependendo das controladoras e versões de firmware. **Esses modelos ainda não foram homologados.**

## Estado atual

**Protótipo web v0.3:** desenvolvido localmente, com tela de abertura de temática pirata, interface de controle simulada e identificação do autor. Os arquivos desta versão ainda precisam ser incorporados ao repositório.

**Firmware ESP32 e impressão real:** ainda não implementados.

A publicação da interface pelo GitHub Pages servirá inicialmente para **demonstração e testes de usabilidade**, não para controle de equipamentos.

## Segurança

Impressoras 3D envolvem partes móveis e sistemas de aquecimento. Antes de qualquer operação real, serão necessários testes de comunicação, tratamento de falhas, limites de movimentação e mecanismos adequados de segurança. O Sabre 3D não substitui as proteções do firmware e do hardware da impressora.

---

**Desenvolvido por DGandra - 2026**
