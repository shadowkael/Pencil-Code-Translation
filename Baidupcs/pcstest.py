#!/usr/bin/env python
# encoding: utf-8
'''
Python client for Baidu Yun (https://github.com/Yungkc0/Baidupcs)
---
It provides file operations like: list, download, upload, syncup, syncdown, etc.
It use BaiDu PCS Demo API key.
---
@author:     yungkc (GitHub: Yungkc0)
'''

import sys
import os
import re
import hashlib
import binascii
from os.path import getsize
from urllib import parse
from datetime import datetime
try:
	import requests
except:
	print("Please install module 'requests'")
	sys.exit()

## const
ApiKey = 'L6g70tBRRIXLsY0Z3HwKqlRE'

OpenApiUrl = "https://openapi.baidu.com"
OpenApiVersion = "2.0"
OAuthUrl = OpenApiUrl + "/oauth/" + OpenApiVersion
ServerAuthUrl = OAuthUrl + "/authorize"
TokenUrl = OAuthUrl + "/token"
PcsUrl = "https://pcs.baidu.com/rest/2.0/pcs/"
CPcsUrl = "https://c.pcs.baidu.com/rest/2.0/pcs/"
DPcsUrl = "https://d.pcs.baidu.com/rest/2.0/pcs/"
AppPcsPath = '/apps/pcstest_oauth'
UserAgent = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:42.0) Gecko/20100101 Firefox/42.0'
MD5NotFound = 31079
DownloadRange = 10 * 1024 * 1024

doc = {       ## 因为内容比较少，所以用一个dict对象模拟HelpDoc
	"help" : "help [command]-display usage of command",
	"quota" : "quota-displays the quota information",
	"ls" : "ls-list the 'pcstest_oauth/' directory at Baidu PCS",
	"download" : "download<filepath> [localpath]-download a remote file to localpath",
	"upload" : "upload <localpath> [remotepath]-upload a file or directory(default use rapidupload)",
	"delete" : "delete a file or directory",
	"move" : "move <form> <to>-move a file or directory from <from> to <to>",
	"mkdir" : "mkdir <dir>-create a directory 'pcstest_oauth/dir'",
	"copy" : "copy <form> <to>-copy a file or directory form <from> to <to>, if <to> does not exist, then create it",
	"find" : "find <keyword> [dir]-search for a file using keyword",
	"exit" : "exit-exit"
}

print("\033[32m")

## functions
def help(token, *cmd):
	if len(cmd) == 2:
		for key in doc:
			print("%s" % doc[key])
	elif len(cmd) == 3:
		try:
			print("Usage:  %s" % doc[cmd[1]])
		except KeyError:
			onexit(1)
	else:
		onexit(1)

def sizef(size):  ## 格式化文件size（字节数）
	if size < 1024:
		size = '{}B'.format(size)
	elif size < 1024*1024:
		size = '{}kB'.format(size //1024)
	elif size < 1024*1024*1024:
		size = '{:.1f}MB'.format(size /1024/1024)
	else:
		size = '{:.2}GB'.format(size /1024/1024/1024)
	return size

def onexit(err):
	if err == 1:
		print("Argument error!")
	else:
		sys.exit()

def onerror(**err):
	print("%d: %s" % (err['error_code'], err['error_msg']))

def pcs_path(path = None):
	if not path or path == '/' or path == '\\':
		return AppPcsPath
	return (AppPcsPath + '/' + path.strip('/')).rstrip('/')

def get_token(uid):
	with open('users', 'r') as f:
		d = eval(f.read())
	if uid in d:
		return d[uid]
	print("Click the link below for authorization\n%s\nwhen page show 'OAuth2.0'， copy URL in to here:" % 
(ServerAuthUrl + "?response_type=token&client_id=" + ApiKey + "&redirect_uri=oob&scope=netdisk"))
	url=input("URL:")  ##使用正则表达式找到url中的token
	try:
		d[uid] = re.search(r'token\=.+&session_secret',url).group(0).strip('token=&session_secret')
	except AttributeError:
		return ''
	with open('users', 'w') as f:
		f.write('{')
		for key in d:
			f.write('\'' + key + '\'' + ':' + '\'' + d[key] + '\'' + ',')
		f.write('}')
	mkdir(d[uid], 'mkdir', '')  ## 第一次使用，需要创建pcstest_oauth/文件夹
	return d[uid]

## APIs(meat, quota, list, download, upload(rapidupload), mkdir, move, copy, dekete, search)
def meta(token, path):
	pars = {
		'method' : 'meta',
		'access_token' : token,
		'path' : path
	}
	r = requests.get(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)
	elif r['list'][0]['isdir']:
		return -1
	else:
		return r['list'][0]['size']
		
def quota(token, *none):
	if len(none) > 2:
		onexit(1)
		return
	pars = {
		'method' : 'info',
		'access_token' : token
	}
	r = requests.get(PcsUrl + 'quota', params = pars).json()
	if 'error_code' in r:
		onerror(r['error_code'])
	else:
		q = r['quota']/1024/1024/1024
		u = r['used']/1024/1024/1024
		print("quota:%dGB  used:%.2fGB  free:%.2fGB" % (q, u, q-u))

def ls(token, *path):
	if len(path) > 3:
		onexit(1)
		return
	pars = {
		'method' : 'list',
		'path' : pcs_path(path[1]),
		'access_token' : token
	}
	r = requests.get(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)
	else:
		if not r['list']:
			print("Invalid directory name or directory is empty.")
		else:
			print("$name      $size      $mtime      $isdir")
			for df in r['list']:
				name = df['path'].split('/')[-1]
				if df['isdir']:
					size = ''
					isdir = 'yes'
				else:
					size = sizef(df['size'])
					isdir = 'no'
				mtime = datetime.fromtimestamp(df['mtime'])
				print("%s   %s   %s   %s" % (name, size, mtime, isdir))

def download(token, *path):
	if len(path) == 4:
		localpath = path[2].rstrip('/') + '/' + path[1].split('/')[-1]
	elif len(path) == 3:
		localpath = path[1].split('/')[-1]
	else:
		onexit(1)
		return
	pars = {
		'method' : 'download',
		'path' : pcs_path(path[1]),
		'access_token' : token
	}
	total = meta(token, pars['path'])
	if not total:
		return
	elif total == -1:
		print("Can't download directory")
		return

	## 使用断点续传
	size = 0
	start_t = datetime.now().timestamp()
	finished = False
	tmp_filename = localpath + '.downtmp'
	try:
		with open(tmp_filename, 'rb') as fin:
			record = eval(fin.read())
			size = record[0]
			start_t = record[1]
	except:
		f = open(tmp_filename, 'w')
		f.close()
		f = open(localpath, 'w')
		f.close()
	headers = {'Range' : 'bytes={}-'.format(size)}

	print("Downloading...")
	r = requests.get(DPcsUrl + 'file',stream = True, verify = False,  params = pars, headers = headers)
	with open(localpath, 'ab') as f:
		try:
			for chunk in r.iter_content(chunk_size = 12345):
				if chunk:
					f.write(chunk)
					size += len(chunk)
					f.flush()
				print('\b' * 64 +"Now: %dB, Total: %sB" % (size, total), end = '')
			if size != total:
				raise TypeError()
			finished = True
			spend = int(datetime.now().timestamp() - start_t)
			speed = int(size / 1024 / spend)
			print("Download finished!\nTotal Time: %ss  Download Speed: %sk/s" % (spend, speed))
			os.remove(tmp_filename)
		except:
			print("Download pause.Try command 'download' again to continue.")
		finally:
			if not finished:
				with open(tmp_filename, 'w') as ftmp:
					ftmp.write("(%d, %d)" % (size, start_t))

def upload(token, *path):
	if len(path) != 4 and len(path) != 3:
		onexit(1)
		return
	print("try rapidupload...")

	## 文件大小
	length = getsize(path[1])
	if length <= 256 * 1024:
		upload_file(token, *path)
		return
	## 计算文件MD5
	m = hashlib.md5()
	with open(path[1], "rb") as f:
		while True:
			buf = f.read(1024 * 1024)
			if buf:
				m.update(buf)
			else:
				break
	md5 = m.digest()
	## 计算文件效验段(前256字节)MD5
	with open(path[1], "rb") as f:
		buf = f.read(256 * 1024)
		m.update(buf)
	slice_md5 = m.digest()
	## 计算文件效验段CRC32
	with open(path[1], "rb") as f:
		buf = f.read(1024 * 1024)
		crc = binascii.crc32(buf)
		while True:
			buf = f.read(1024 * 1024)
			if buf:
				crc = binascii.crc32(buf, crc)
			else:
				break
	crc32 = crc & 0xffffffff

	filename = path[1].split('/')[-1]
	pars = {
		'method' : 'rapidupload',
		'content-length' : length,
		'content-md5' : binascii.hexlify(md5),
		'slice-md5' : binascii.hexlify(slice_md5),
		'content-crc32' : hex(crc32),
		'path' : pcs_path(path[2]) + '/' + filename,
		'access_token' : token,
		'ondup' : 'overwrite'
	}
	r = requests.post(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r and r['error_code'] == MD5NotFound:
		t = input("file md5 not found, upload whole file?(y or n)").lower()
		if t == 'y' or t == 'yes':
			upload_file(token, *path)
	elif 'size' in r:
		print("%s  %s  %s" % (filename, sizef(r['size']), r['md5']))
		print("Rapidupload successfully!")
	else:
		onerror(**r)

def upload_file(token, *path):
	filename = path[1].split('/')[-1]
	pars = {
		'method' : 'upload',
		'path' : pcs_path(path[2]) + '/' + filename,
		'access_token' : token,
		'ondup' : 'overwrite'
	}
	with open(path[1], 'rb') as f:
		print("Uploading...")
		r = requests.post(CPcsUrl + 'file', params = pars, files = {'file' : f}).json()
	if 'error_code' in r:
		onerror(**r)
	else:
		print("%s  %s  %s" % (filename, sizef(r['size']), r['md5']))
		print("Upload successfully!")

def mkdir(token, *path):
	if len(path) > 3:
		onexit(1)
		return
	pars = {
		'method' : 'mkdir',
		'path' : pcs_path(path[1]),
		'access_token' : token
	}
	r = requests.post(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)

def move(token, *path):
	if len(path) != 4:
		onexit(1)
		return
	temp =  pcs_path(path[1])
	pars = {
		'method' : 'move',
		'from' : temp,
		'to' : pcs_path(path[2]) + '/' + temp.split('/')[-1],
		'access_token' : token
	}
	r = requests.post(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)
	else:
		print("Move successfully!")

def copy(token, *path):
	if len(path) != 4:
		onexit(1)
		return
	temp =  pcs_path(path[1])
	pars = {
		'method' : 'copy',
		'from' : temp,
		'to' : pcs_path(path[2]) + '/' + temp.split('/')[-1],
		'access_token' : token
	}
	r = requests.post(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)
	else:
		print("Copy successfully!") 

def delete(token, *path):
	if len(path) != 3:
		onexit(1)
		return
	pars = {
		'method' : 'delete',
		'path' : pcs_path(path[1]),
		'access_token' : token
	}
	r = requests.post(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)
	else:
		print("Delete successfully!")

def find(token, *wd):
	if len(wd) != 4 and len(wd) != 3:
		onexit(1)
		return
	pars = {
		'method' : 'search',
		'path' : pcs_path(wd[2]),
		'wd' : wd[1],
		're' : 1,
		'access_token' : token
	}
	r = requests.get(PcsUrl + 'file', params = pars).json()
	if 'error_code' in r:
		onerror(**r)
	else:
		if not len(r['list']):
			print("Can't find anything")
		else:
			print("$path      $size      $md5")
			for ds in r['list']:
				size = sizef(ds['size'])
				print("%s  %s  %s" % (ds['path'].replace(pars['path'], ''), size, ds['md5']))

## main()
def main():
	exe = {'copy' : copy, 'find' : find, 'delete' : delete,
		'move' : move, 'mkdir' : mkdir, 'upload' : upload,
		'download' : download, 'ls' : ls, 'quota' : quota,
		'help' : help
	}
	uid = input("userId:")
	token = get_token(uid)
	if token == '':
		print("Token Error!!!")
		onexit(0)
	print("Input 'help' to get help")
	cmd=input(">>>")
	while(cmd != "exit"):
		cmd = cmd.strip().split(' ')
		cmd.append('')
		if cmd[0] == '':
			cmd = input(">>>")
			continue
		def bypy(*cmd):  ##模拟switch/case语句
			try:
				exe.get(cmd[0])(token, *cmd)
			except TypeError:
				print("Command not found!")
		try:
			bypy(*cmd)
		except FileNotFoundError as e:
			print(e)
		except PermissionError as e:
			print(e)
		cmd = input(">>>")

if __name__ == "__main__":
	try:
		main()
	except KeyboardInterrupt:
		onexit(0)

# gedit: Tab Width=4 encoding=utf-8
