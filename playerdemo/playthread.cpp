#include <QDebug>
#include <QTime>

#include "playthread.h"
#include "videodataoprator.h"
#include "videoctl.h"

PlayThread::PlayThread()
{
	window = nullptr;
	renderer = nullptr;

	vid_texture = nullptr;

	m_WId = 0;


	img_convert_ctx = nullptr;
}


PlayThread::~PlayThread()
{
}

void PlayThread::OnStarPlay(WId wid)
{
	m_WId = wid;
	StartThread();
}


int PlayThread::realloc_texture(SDL_Texture **texture, Uint32 new_format, int new_width, int new_height, SDL_BlendMode blendmode, int init_texture)
{
	Uint32 format = 0;
	int access = 0, w = 0, h = 0;

	int nRet = 0;
	nRet = SDL_QueryTexture(*texture, &format, &access, &w, &h);
	if (nRet < 0 || new_width != w || new_height != h || new_format != format) {
		void *pixels;
		int pitch;
		SDL_DestroyTexture(*texture);
		if (!(*texture = SDL_CreateTexture(renderer, new_format, SDL_TEXTUREACCESS_STREAMING, new_width, new_height)))
			return -1;
		if (SDL_SetTextureBlendMode(*texture, blendmode) < 0)
			return -1;
		if (init_texture) {
			if (SDL_LockTexture(*texture, NULL, &pixels, &pitch) < 0)
				return -1;
			memset(pixels, 0, pitch * new_height);
			SDL_UnlockTexture(*texture);
		}
	}
	return 0;
}

int PlayThread::upload_texture(SDL_Texture *tex, AVFrame *frame, struct SwsContext **img_convert_ctx)
{
	int ret = 0;
	switch (frame->format) {
	case AV_PIX_FMT_YUV420P:
		if (frame->linesize[0] < 0 || frame->linesize[1] < 0 || frame->linesize[2] < 0) {
			av_log(NULL, AV_LOG_ERROR, "Negative linesize is not supported for YUV.\n");
			return -1;
		}
		ret = SDL_UpdateYUVTexture(tex, NULL, frame->data[0], frame->linesize[0],
			frame->data[1], frame->linesize[1],
			frame->data[2], frame->linesize[2]);
		break;
	case AV_PIX_FMT_BGRA:
		if (frame->linesize[0] < 0) {
			ret = SDL_UpdateTexture(tex, NULL, frame->data[0] + frame->linesize[0] * (frame->height - 1), -frame->linesize[0]);
		}
		else {
			ret = SDL_UpdateTexture(tex, NULL, frame->data[0], frame->linesize[0]);
		}
		break;
	default:
		/* This should only happen if we are not using avfilter... */
		*img_convert_ctx = sws_getCachedContext(*img_convert_ctx,
			frame->width, frame->height, (AVPixelFormat)frame->format, frame->width, frame->height,
			AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);
		if (*img_convert_ctx != NULL) {
			uint8_t *pixels[4];
			int pitch[4];
			if (!SDL_LockTexture(tex, NULL, (void **)pixels, pitch)) {
				sws_scale(*img_convert_ctx, (const uint8_t * const *)frame->data, frame->linesize,
					0, frame->height, pixels, pitch);
				SDL_UnlockTexture(tex);
			}
		}
		else {
			av_log(NULL, AV_LOG_FATAL, "Cannot initialize the conversion context\n");
			ret = -1;
		}
		break;
	}
	return ret;
}



void PlayThread::run()
{
	qDebug() << "PlayThread::run";
	//SDL_CreateWindowFrom
	//SDL_GetWindowSize
	//SDL_DestroyWindow

	//SDL_UpdateYUVTexture
	//SDL_UpdateTexture
	//SDL_RenderCopyEx
	//SDL_RenderCopy

	bool bRet;

	VideoDataOprator *pVideoDataOprator = VideoCtl::GetInstance()->GetVideoDataOprator();

	AVFrame avframe;

	//SDL初始化
	int flags;
	flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
	if (SDL_Init(flags) < 0)
	{
		qDebug() << "SDL could not be Init! SDL_Error:" << SDL_GetError();
		return;
	}

	//由已有窗口创建sdl窗口
	window = SDL_CreateWindowFrom((void *)m_WId);

	if (window)
	{
		SDL_RendererInfo info;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer)
		{
			av_log(NULL, AV_LOG_WARNING, "Failed to initialize a hardware accelerated renderer: %s\n", SDL_GetError());
			renderer = SDL_CreateRenderer(window, -1, 0);
		}
		if (renderer)
		{
			if (!SDL_GetRendererInfo(renderer, &info))
				qDebug("Initialized %s renderer.\n", info.name);
		}
	}


	if (!window || !renderer) 
	{
		av_log(NULL, AV_LOG_FATAL, "SDL: could not set video mode - exiting\n");
		qDebug() << "Window could not be created! SDL_Error:" << SDL_GetError();
		return;
	}

	QTime t;
	while (m_bRunning)
	{
		t.restart();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		bRet = pVideoDataOprator->GetDataDec(avframe, VIDEO_DATA);
		if (bRet == false)
		{
			continue;
		}

		int sdl_pix_fmt = avframe.format == AV_PIX_FMT_YUV420P ? SDL_PIXELFORMAT_YV12 : SDL_PIXELFORMAT_ARGB8888;

		if (realloc_texture(&vid_texture, sdl_pix_fmt, avframe.width, avframe.height, SDL_BLENDMODE_NONE, 0) < 0)
			return;
		if (upload_texture(vid_texture, &avframe, &img_convert_ctx) < 0)
			return;

		int flip_v = avframe.linesize[0] < 0;
		SDL_RenderCopyEx(renderer, vid_texture, NULL, NULL, 0, NULL, (flip_v ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE));

		SDL_RenderPresent(renderer);

		msleep(40);//30fps
	}
	

}
