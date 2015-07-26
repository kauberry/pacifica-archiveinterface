#!/usr/bin/python
"""
MyEMSL Archive Interface

This is the main program that starts the WSGI server.

The core of the server code is in archive_interface.py.
"""
from argparse import ArgumentParser
from archive_interface import archive_generator
from wsgiref.simple_server import make_server

# 
parser = ArgumentParser(description='Run the archive interface.')

parser.add_argument('-p', '--port', metavar='PORT', type=int, 
    nargs=1, default=8080, dest='port', 
    help="port to listen on")
parser.add_argument('-a', '--address', metavar='PORT', nargs=1, 
    default='localhost', dest='address', 
    help="address to listen on")
parser.add_argument('-t', '--type', dest='type', default='hpss',
    choices=['hpss', 'posix'], help='use the typed backend')

args = parser.parse_args()
srv = make_server(args.address[-1], args.port[-1], 
  archive_generator(args.type[-1]))
srv.serve_forever()