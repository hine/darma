import os
import sys
import time
import json
import threading

import tornado.ioloop
import tornado.web
import tornado.websocket

clients = []

class IndexHandler(tornado.web.RequestHandler):
    '''
    通常のHTTPリクエストで/が求められた時のハンドラ
    '''
    @tornado.web.asynchronous
    def get(self):
        self.render("index.html")


class WebSocketHandler(tornado.websocket.WebSocketHandler):
    '''
    WebSocketで/wsにアクセスが来た時のハンドラ
    on_message -> receive data
    write_message -> send data
    '''

    def open(self):
        print('WebSocket opened')
        clients.append(self)

    def check_origin(self, origin):
        ''' アクセス元チェックをしないように変更 '''
        return True

    def on_message(self, message):
        ''' メッセージを受け取ったら、そのまま全てのクライアントに転送 '''
        #print(message)
        for client in clients:
            client.write_message(message)
        #received_data = json.loads(message)
        #print('got message:', received_data['pin'], ":", received_data['value'])

    def on_close(self):
        clients.remove(self)
        print('WebSocket closed')


# アプリケーション割り当て
web_application = tornado.web.Application([
    (r'/', IndexHandler),
    (r'/ws', WebSocketHandler),
    ],
    template_path=os.path.join(os.getcwd(),  'templates'),
    static_path=os.path.join(os.getcwd(),  'assets'),
)

if __name__ == '__main__':

    # Tornado起動
    print('Starting Web/WebSocket Server...', end='')
    web_application.listen(8888)
    print('done')
    print('')

    # Tornadoメインループ
    tornado.ioloop.IOLoop.instance().start()
