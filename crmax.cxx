// a test routine for regional extrema using flooding
#include "itkRegionalMaximaImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSimpleFilterWatcher.h"
#include "itkBinaryFunctorImageFilter.h"
#include "itkConnectedComponentImageFilter.h"

template< class TInputPixel, class TLabel, class TRGBPixel >
class LabelOverlay
{
public:
  LabelOverlay()
    {
    TRGBPixel rgbPixel;
    typename TRGBPixel::ValueType m = itk::NumericTraits< typename TRGBPixel::ValueType >::max();
    typename TRGBPixel::ValueType z = itk::NumericTraits< typename TRGBPixel::ValueType >::Zero;
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( m, m/2, z); // orange 30
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( m, m, z); // yellow 60
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( m/2, m, z); // 90
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( z, m, z); // green 120
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( z, m, m/2); // 150
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( z, m, m); // cyan 180
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( z, m/2, m); // 210
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( z, z, m); // blue 240
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( m/2, z, m); // 270
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( m, z, m); // violet 300
    m_Colors.push_back( rgbPixel );
    rgbPixel.Set( m, z, m/2); // 330
    m_Colors.push_back( rgbPixel );
    }
  ~LabelOverlay() {}
  inline TRGBPixel operator()(  const TInputPixel & p1,
                                 const TLabel & p2)
  {
    if( p2 == itk::NumericTraits< TLabel >::Zero )
      {
      typename TRGBPixel::ValueType p = static_cast< typename TRGBPixel::ValueType >( p1 );
      TRGBPixel rgbPixel;
      rgbPixel.Set( p, p, p );
      return rgbPixel;
      }
    return m_Colors[ p2 % m_Colors.size() ];
  }
  bool operator != (const LabelOverlay&) const
  {
    return false;
  }
  std::vector< TRGBPixel > m_Colors;
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

  typedef itk::RegionalMaximaImageFilter< IType, IType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetFullyConnected( atoi(argv[1]) );
  itk::SimpleFilterWatcher watcher(filter, "filter");

  typedef itk::ConnectedComponentImageFilter< IType, LIType > ConnectedType;
  ConnectedType::Pointer connected = ConnectedType::New();
  connected->SetInput( filter->GetOutput() );
  connected->SetFullyConnected( atoi(argv[1]) );

  typedef LabelOverlay< PType, LPType, CPType > LabelOverlayType;
  typedef itk::BinaryFunctorImageFilter< IType, LIType, CIType, LabelOverlayType > ColorMapFilterType;
  ColorMapFilterType::Pointer colormapper = ColorMapFilterType::New();
  colormapper->SetInput1( reader->GetOutput() );
  colormapper->SetInput2( connected->GetOutput() );

  typedef itk::ImageFileWriter< CIType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( colormapper->GetOutput() );
  writer->SetFileName( argv[3] );
  writer->Update();


  return 0;
}

