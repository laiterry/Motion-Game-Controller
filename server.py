#!/usr/bin/env python

# -*- Coding: UTF-8 -*-
# @Time    : 12/8/18 7:02 PM
# @Author  : Terry LAI
# @Email   : terry.lai@hotmail.com
# @File    : keyboard.py

from pymouse import PyMouse
from pykeyboard import PyKeyboard
from socket import socket, AF_INET, SOCK_STREAM

port = 20000
# -*- coding: utf-8 -*-

client_addr = []
client_socket = {}

###########################################################################
## Python code generated with wxFormBuilder (version Sep 12 2010)
## http://www.wxformbuilder.org/
##
## PLEASE DO "NOT" EDIT THIS FILE!
###########################################################################

import wx
from socketserver import ThreadingTCPServer

###########################################################################
## Class MotionGame
###########################################################################

class MotionGame(wx.Frame):

    def __init__(self, parent):
        wx.Frame.__init__(self, parent, id=wx.ID_ANY, title=wx.EmptyString, pos=wx.DefaultPosition,
                          size=wx.Size(500, 300), style=wx.DEFAULT_FRAME_STYLE | wx.TAB_TRAVERSAL)

        self.SetSizeHintsSz(wx.DefaultSize, wx.DefaultSize)

        bSizer11 = wx.BoxSizer(wx.VERTICAL)

        self.m_staticText1 = wx.StaticText(self, wx.ID_ANY, u"ECE 5413 Motion Game", wx.DefaultPosition, wx.DefaultSize,
                                           0)
        self.m_staticText1.Wrap(-1)
        bSizer11.Add(self.m_staticText1, 0, wx.ALL | wx.ALIGN_CENTER_HORIZONTAL, 5)

        self.m_button1 = wx.Button(self, wx.ID_ANY, u"Start Server", wx.DefaultPosition, wx.DefaultSize, 0)
        bSizer11.Add(self.m_button1, 0, wx.ALL | wx.ALIGN_CENTER_HORIZONTAL, 5)

        self.m_staticText2 = wx.StaticText(self, wx.ID_ANY, u"server is down", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText2.Wrap(-1)
        bSizer11.Add(self.m_staticText2, 0, wx.ALL | wx.ALIGN_CENTER_HORIZONTAL, 5)

        gbSizer1 = wx.GridBagSizer(0, 0)
        gbSizer1.SetFlexibleDirection(wx.BOTH)
        gbSizer1.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)

        self.m_staticText12 = wx.StaticText(self, wx.ID_ANY, u"Game 1", wx.Point(20, 20), wx.DefaultSize,
                                            wx.ALIGN_CENTRE)
        self.m_staticText12.Wrap(-1)
        gbSizer1.Add(self.m_staticText12, wx.GBPosition(0, 0), wx.GBSpan(1, 1),
                     wx.ALL | wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT, 5)

        self.m_button2 = wx.Button(self, wx.ID_ANY, u"Set Game 1", wx.DefaultPosition, wx.DefaultSize, 0)
        gbSizer1.Add(self.m_button2, wx.GBPosition(0, 1), wx.GBSpan(1, 1), wx.ALL, 5)

        self.m_staticText14 = wx.StaticText(self, wx.ID_ANY, u"Player 1", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText14.Wrap(-1)
        gbSizer1.Add(self.m_staticText14, wx.GBPosition(0, 2), wx.GBSpan(1, 1), wx.ALL, 5)

        self.m_staticText4 = wx.StaticText(self, wx.ID_ANY, u"disconnected", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText4.Wrap(-1)
        gbSizer1.Add(self.m_staticText4, wx.GBPosition(0, 3), wx.GBSpan(1, 1), wx.ALL, 5)

        bSizer11.Add(gbSizer1, 1, wx.EXPAND, 5)

        gbSizer11 = wx.GridBagSizer(0, 0)
        gbSizer11.SetFlexibleDirection(wx.BOTH)
        gbSizer11.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)

        self.m_staticText121 = wx.StaticText(self, wx.ID_ANY, u"Game 2", wx.Point(20, 20), wx.DefaultSize,
                                             wx.ALIGN_CENTRE)
        self.m_staticText121.Wrap(-1)
        gbSizer11.Add(self.m_staticText121, wx.GBPosition(0, 0), wx.GBSpan(1, 1),
                      wx.ALL | wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_RIGHT, 5)

        self.m_button3 = wx.Button(self, wx.ID_ANY, u"Set Game 2", wx.DefaultPosition, wx.DefaultSize, 0)
        gbSizer11.Add(self.m_button3, wx.GBPosition(0, 1), wx.GBSpan(1, 1), wx.ALL, 5)

        self.m_staticText141 = wx.StaticText(self, wx.ID_ANY, u"Player 1", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText141.Wrap(-1)
        gbSizer11.Add(self.m_staticText141, wx.GBPosition(0, 2), wx.GBSpan(1, 1), wx.ALL, 5)

        self.m_staticText5 = wx.StaticText(self, wx.ID_ANY, u"disconnected", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText5.Wrap(-1)
        gbSizer11.Add(self.m_staticText5, wx.GBPosition(0, 3), wx.GBSpan(1, 1), wx.ALL, 5)

        self.m_staticText40 = wx.StaticText(self, wx.ID_ANY, u"Player 2", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText40.Wrap(-1)
        gbSizer11.Add(self.m_staticText40, wx.GBPosition(0, 4), wx.GBSpan(1, 1), wx.ALL, 5)

        self.m_staticText6 = wx.StaticText(self, wx.ID_ANY, u"disconnected", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText6.Wrap(-1)
        gbSizer11.Add(self.m_staticText6, wx.GBPosition(0, 5), wx.GBSpan(1, 1), wx.ALL, 5)



        bSizer11.Add(gbSizer11, 1, wx.EXPAND, 5)

        bSizer12 = wx.BoxSizer(wx.VERTICAL)

        self.m_staticText57 = wx.StaticText(self, wx.ID_ANY, u"Game 2 Link: ", wx.DefaultPosition, wx.Size(50, -1), 0)
        self.m_staticText57.Wrap(-1)
        self.m_staticText57.SetMaxSize(wx.Size(100, -1))

        bSizer12.Add(self.m_staticText57, 1, wx.ALL | wx.EXPAND, 5)

        self.m_textCtrl12 = wx.TextCtrl(self, wx.ID_ANY, u"http://www.4399.com/flash/187228_1.htm", wx.DefaultPosition,
                                        wx.DefaultSize, 0)
        bSizer12.Add(self.m_textCtrl12, 0, wx.ALL | wx.EXPAND, 5)

        bSizer11.Add(bSizer12, 1, wx.EXPAND, 5)

        self.SetSizer(bSizer11)
        self.Layout()

        self.Centre(wx.BOTH)

        # Connect Events
        self.m_button1.Bind(wx.EVT_BUTTON, self.start_server)
        self.m_button2.Bind(wx.EVT_BUTTON, self.set_game1)
        self.m_button3.Bind(wx.EVT_BUTTON, self.set_game2)

    def __del__(self):
        pass

    # Virtual event handlers, overide them in your derived class
    def start_server(self, event):
        frame.m_staticText2.SetLabel("Server is Running !!! ")

        print("start server")
        timer = threading.Timer(timer_period, fun_timer)
        timer.start()
        # 第一对参数是（host, port）
        server = ThreadingTCPServer(('', port), EchoHandler)

        server_thread = threading.Thread(target=server.serve_forever)
        # Exit the server thread when the main thread terminates
        server_thread.daemon = True
        server_thread.start()
        #sudo netstat -lntup|grep 20000
        #ps -ef|grep python  // 查看在python中的所有进程
        #kill -9 51976  // -9指是强制关闭进程，有时候直接用`kill 51976`是杀不死进程的



    def set_game1(self, event):
        global mode
        global mode_1_flag
        global mode_2_flag
        mode_1_flag = True
        mode = 1
        print("Mode 1")
        for key,value in client_socket.items():
            value.sendall(bytes([0x11,0x22,0x33]))


    def set_game2(self, event):
        global mode
        global mode_1_flag
        global mode_2_flag
        mode_2_flag = True
        mode = 2
        print("Mode 2")
        for key,value in client_socket.items():
            try:
                value.sendall(bytes([0x11, 0x22, 0x33]))
            except IOError:
                pass
            else:
                pass


m = PyMouse()
k = PyKeyboard()


from socketserver import BaseRequestHandler, TCPServer

buffer_size = 10

key_flag = False
import threading

timer_period = 0.1
def fun_timer():
    global key_flag
    #print('Hello Timer!')
    key_flag = True
    global timer
    timer = threading.Timer(timer_period, fun_timer)
    timer.start()

previous_key = 0

mode = 1
frame =None

mode_1_flag= False
mode_2_flag= False

d = {}

# 继承BaseRequestHandler这个base class，并重定义handle()
class EchoHandler(BaseRequestHandler):

    def setup(self):
        ip = self.client_address[0].strip()     # 获取客户端的ip
        port = self.client_address[1]           # 获取客户端的port
        print(ip+":"+str(port)+" is connect!")
        client_addr.append(self.client_address) # 保存到队列中
        client_socket[self.client_address] = self.request # 保存套接字socket

    def finish(self):
        print("client is disconnect!")
        client_addr.remove(self.client_address)
        del client_socket[self.client_addr]

    def handle(self):
        global key_flag
        global previous_key
        global mode_1_flag
        global mode_2_flag
        print('Got connection from', self.client_address)

        print(type(self.request))

        # self.request is the TCP socket connected to the client
        count = 0
        msg = []



        while True:
            # 8192代表每次读取8192字节
            temp = self.request.recv(buffer_size)
            msg.extend(temp)

            while len(msg) >= 2 and (msg[0]!=0xa0 or msg[1]!=0xa1):
                msg.pop(0)

            if len(msg)<buffer_size:
                continue

            if not key_flag:
                continue

            up  = msg[2]
            down  = msg[3]
            left  = msg[4]
            right  = msg[5]
            node = msg[6]

            if node == 1:
                frame.m_staticText4.SetLabel("Connected !!! ")
                frame.m_staticText5.SetLabel("Connected !!! ")

            if node == 2:
                frame.m_staticText6.SetLabel("Connected !!! ")

            if mode == 1:

                key = 0
                if up and not left and not right:
                    key =1
                if down and not left and not right:
                    key =2
                if left:
                    key =3
                if right:
                    key =4


                if key != 0 and previous_key != key:
                    print(key)
                    if key == 1:
                        k.press_key("up")
                        print(" node 1 up")

                    # else:
                    #     k.release_key("up")

                    if key == 2:
                        k.press_key("down")
                        print(" node 1 down")

                    # else:
                    #     k.release_key("down")

                    if key == 3:
                        k.press_key("left")
                        print(" node 1 left")

                    # else:
                    #     k.release_key("left")

                    if key == 4:
                        k.press_key("right")
                        print(" node 1 right")

                    # else:
                    #     k.release_key("right")

                previous_key = key


            if mode == 2:

                if node == 1:

                    if up == 1:
                        k.press_key("up")
                        print(" node 1 up")
                    else:
                        k.release_key("up")

                    if down == 1:
                        k.press_key("down")
                        print(" node 1 down")
                    else:
                        k.release_key("down")

                    if left == 1:
                        k.press_key("left")
                        print(" node 1 left")
                    else:
                        k.release_key("left")

                    if right == 1:
                        k.press_key("right")
                        print(" node 1 right")
                    else:
                        k.release_key("right")

                if node == 2:

                    if up == 1:
                        k.press_key("w")
                        print(" node 2 up")
                    else:
                        k.release_key("w")

                    if down == 1:
                        k.press_key("s")
                        print(" node 2 down")
                    else:
                        k.release_key("s")

                    if left == 1:
                        k.press_key("a")
                        print(" node 2 left")
                    else:
                        k.release_key("a")

                    if right == 1:
                        k.press_key("d")
                        print(" node 2 right")
                    else:
                        k.release_key("d")



            msg = []
            #key_flag = False



if __name__ == '__main__':

    app = wx.App()  # 实例化一个主循环<br>
    frame = MotionGame(None)  # 实例化一个窗口<br>
    frame.Show()  # 调用窗口展示功能<br>

    app.MainLoop()  # 启动主循环




