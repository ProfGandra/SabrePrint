# Sabre 3D — Autenticação e permissões

**Status:** arquitetura aprovada; implementação pendente.

## Modelo de acesso

O sistema terá **duas contas/perfis autenticados: master e usuário comum**, além do visitante sem login. A configuração inicial de credenciais e sua recuperação serão definidas antes da implementação.

O ESP32-S3 opera em SoftAP `Sabre3D` e serve a interface em `http://192.168.4.1`.

| Permissão | Visitante | Usuário comum | Master |
|---|---|---|---|
| Visualizar estado, temperaturas, progresso e arquivo | Sim | Sim | Sim |
| Enviar arquivos G-code ao microSD | Não | Sim | Sim |
| Iniciar, pausar, retomar e cancelar impressão | Não | Sim | Sim |
| Movimentar eixos e ajustar temperaturas | Não | Sim | Sim |
| Enviar comandos pelo terminal G-code | Não | Sim | Sim |
| Alterar configurações administrativas e de rede | Não | Não | Sim |
| Gerenciar contas e senhas de outros usuários | Não | Não | Sim |
| Atualizar firmware | Não | Não | Sim |

**Master:** administrador do equipamento. **Usuário comum:** operador de impressão. **Visitante:** consulta em modo somente leitura.


## Requisitos de segurança

- A autorização é **validada no firmware em cada endpoint e comando WebSocket**, nunca apenas ocultando botões na interface.
- A senha dos usuários não deve ser gravada em texto puro no firmware ou no repositório. Armazenar derivação criptográfica com sal; definir credencial inicial individual ou provisionamento local.
- Sessões com token aleatório de curta duração vinculado ao perfil, expiração por inatividade e opção de sair. Invalidar sessões após troca de senha.
- Proteger contra tentativas repetidas de login com limitação de taxa e atraso progressivo.
- O SoftAP deve usar WPA2 e senha de rede própria, distinta da senha do operador.
- **Atenção:** HTTP sem TLS em Wi-Fi local não protege as credenciais de um atacante que tenha acesso à rede. A implantação precisa avaliar HTTPS ou outro mecanismo seguro de autenticação antes de operar impressoras reais; WPA2 não substitui a proteção da sessão.
- Dados sensíveis (senhas/tokens) nunca devem aparecer em logs, URLs ou arquivos de interface estática.
- A parada de emergência e as proteções térmicas devem existir independentemente da autenticação web.

## Estado compartilhado

Todos os visitantes e operadores recebem o mesmo estado do trabalho atual. Somente operadores autenticados podem alterá-lo. O servidor rejeita tentativa de iniciar um segundo trabalho enquanto houver impressão ativa.

## Interface

- Ao abrir: painel em modo **visualização**.
- Botão **Entrar** abre autenticação para usuário comum ou master.
- Após login: habilitar somente controles autorizados e indicar o perfil conectado (**Usuário comum** ou **Master**).
- Botão **Sair** retorna ao modo visualização.
- Se a sessão expirar: bloquear imediatamente novos comandos e solicitar novo login, sem interromper uma impressão já em andamento.

## Pendências de implementação

Definir provisionamento e recuperação das duas contas, duração da sessão, política de múltiplos operadores e proteção das credenciais no ambiente SoftAP. A autorização por perfil deve ser verificada no servidor em toda requisição.

Desenvolvido por DGandra - 2026.
