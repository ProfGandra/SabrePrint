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


## Sessões simultâneas por categoria

**Regra obrigatória:** no máximo **uma sessão Master ativa** e **uma sessão de usuário comum ativa** por vez. Os dois perfis podem coexistir, mas nunca haverá duas sessões simultâneas do mesmo perfil. Visitantes não têm limite lógico de sessão, respeitando apenas a capacidade de conexões do ESP32.

- **Master:** um novo login com credenciais válidas substitui a sessão Master anterior. O servidor invalida imediatamente o token antigo, libera a nova sessão e notifica o navegador anterior, que volta ao modo visitante. Se a notificação em tempo real falhar, qualquer próxima chamada do token antigo será rejeitada.
- **Usuário comum:** um novo login enquanto já existir sessão ativa é **recusado pelo servidor**, com mensagem clara.
- A transferência de sessão Master **não interrompe a impressão em andamento** nem libera a execução de comandos pendentes sem validação.
- O bloqueio é por **perfil**, inclusive entre abas ou dispositivos distintos; não basta limitar a interface.
- A sessão deve ter identificador/token aleatório, estado no ESP32 e expiração controlada pelo servidor.
- O botão **Sair** invalida a sessão imediatamente.
- Fechamento abrupto de aba, queda de Wi-Fi ou desligamento do dispositivo não pode manter o perfil bloqueado indefinidamente: aplicar prazo de expiração e renovação de sessão enquanto houver atividade.
- Não derrubar silenciosamente a sessão anterior: a sessão Master substituída recebe aviso de desconexão. O usuário comum não pode tomar a sessão ativa.
- O acesso simultâneo de Master e usuário comum **não** autoriza comandos incompatíveis: o gerenciador único de impressão continua serializando e validando as operações.
- Reinicialização do ESP32 invalida sessões anteriores; não presume retomada segura de impressão.

**A definir na implementação:** duração da expiração, mecanismo de renovação, recuperação administrativa de sessão bloqueada e política de conflito quando Master e operador enviam comandos ao mesmo tempo.

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

Definir provisionamento e recuperação das duas contas, duração da sessão, política de conflitos entre master e operador e proteção das credenciais no ambiente SoftAP. A autorização por perfil deve ser verificada no servidor em toda requisição.

Desenvolvido por DGandra - 2026.
