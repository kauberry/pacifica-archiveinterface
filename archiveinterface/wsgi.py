#!/usr/bin/python
"""
Pacifica Archive Interface

This is the main program that starts the WSGI server.

The core of the server code is in archive_interface.py.

Any new Backends added need to have the type argument extended
to support the new Backend Archie type

"""
from os import getenv
from argparse import ArgumentParser
from wsgiref.simple_server import make_server
from archiveinterface.archive_interface import ArchiveInterfaceGenerator
from archiveinterface.archivebackends.archive_backend_factory import \
     ArchiveBackendFactory

BACKEND_TYPE = getenv('PAI_BACKEND_TYPE', 'posix')
PREFIX = getenv('PAI_PREFIX', '/tmp')
USER = getenv('PAI_USERNAME', 'user')
AUTH = getenv('PAI_AUTHINFO', 'auth')

#Get the specified Backend Archive
FACTORY = ArchiveBackendFactory()
BACKEND = FACTORY.get_backend_archive(
    BACKEND_TYPE,
    PREFIX,
    USER,
    AUTH
)
#Create the archive interface
GENERATOR = ArchiveInterfaceGenerator(BACKEND)
application = GENERATOR.pacifica_archiveinterface
