// a test routine for regional extrema using flooding
#include "itkRegionalMinimaImageFilter.h"
#include "itkNaryAddImageFilter.h"
#include "itkInvertIntensityImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkAndImageFilter.h"
#include "itkSimpleFilterWatcher.h"
#include "itkComposeRGBImageFilter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkConnectedComponentImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

template< class TPixel >
class AddRGB
{
public:
  AddRGB() {}
  ~AddRGB() {}
  inline TPixel operator()(  const TPixel & p1,
                                 const TPixel & p2)
  {
    TPixel rgbPixel;
    rgbPixel.Set( p1.GetRed() + p2.GetRed(),
                  p1.GetGreen() + p2.GetGreen(),
                  p1.GetBlue() + p2.GetBlue());
    return rgbPixel;
  }
  bool operator != (const AddRGB&) const
  {
    return false;
  }
};


int main(int, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef unsigned long LPType;
  typedef itk::Image< LPType, dim > LIType;

  typedef itk::RGBPixel<unsigned char> CPType;
  typedef itk::Image< CPType, dim > CIType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[2] );

  typedef itk::RegionalMinimaImageFilter< IType, IType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetFullyConnected( atoi(argv[1]) );
  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::InvertIntensityImageFilter< IType, IType > InvertType;
  InvertType::Pointer invert = InvertType::New();
  invert->SetInput( filter->GetOutput() );
  
  typedef itk::AndImageFilter< IType, IType, IType > AndType;
  AndType::Pointer a = AndType::New();
  a->SetInput(0, invert->GetOutput() );
  a->SetInput(1, reader->GetOutput() );
  
  typedef itk::ComposeRGBImageFilter< IType, CIType > ComposeType;
  ComposeType::Pointer compose = ComposeType::New();
  compose->SetInput( 0, a->GetOutput() );
  compose->SetInput( 1, a->GetOutput() );
  compose->SetInput( 2, a->GetOutput() );

  typedef itk::ConnectedComponentImageFilter< IType, LIType > ConnectedType;
  ConnectedType::Pointer connected = ConnectedType::New();
  connected->SetInput( filter->GetOutput() );
  connected->SetFullyConnected( atoi(argv[1]) );

  typedef itk::RescaleIntensityImageFilter< LIType, LIType > RescaleType;
  RescaleType::Pointer rescale = RescaleType::New();
  rescale->SetInput( connected->GetOutput() );

  typedef itk::Functor::ScalarToRGBPixelFunctor< LPType > ColorMapFunctorType;
  typedef itk::UnaryFunctorImageFilter<LIType, CIType, ColorMapFunctorType> ColorMapFilterType;
  ColorMapFilterType::Pointer colormapper = ColorMapFilterType::New();
  colormapper->SetInput( rescale->GetOutput() );

  typedef AddRGB< CPType > RGBAddFunctorType;
  typedef itk::BinaryFunctorImageFilter< CIType, CIType, CIType, RGBAddFunctorType > AddType;
  AddType::Pointer add = AddType::New();
  add->SetInput( 0, colormapper->GetOutput() );
  add->SetInput( 1, compose->GetOutput() );

  typedef itk::ImageFileWriter< CIType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( add->GetOutput() );
  writer->SetFileName( argv[3] );
  writer->Update();


  return 0;
}

